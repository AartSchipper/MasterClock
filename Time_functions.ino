
// UTC time to local Siderial time in seconds function 
// Note: the time.year counter has a range of 0-99 

uint32_t currentSiderealSecond(Clock::time_t &time) { // Needs LONGITUDE
     // sidereal calculation constants
     const float    dc =    0.0657098244,
                    tc =    1.00273791,
                    g2000 = 6.5988098,
                    lc =    0.0497958, 
                    nc =   -0.015914,
                    siderealday = 23.9344699; 
     
     // calculate G (based on extrapolation)
     int16_t g = BCD::bcd_to_int(time.year);
     
     int16_t leap = int((g+1.0)/4.0);                              // number of leap years since 2000
     int16_t nleap = g-leap;                                       // number of non-leap years since 2000   
     float G = g2000 + leap*lc + nleap*nc;                    
     
    // calculate number of days since beginning of year
    int nd = doNumDays(BCD::bcd_to_int(time.year), BCD::bcd_to_int(time.month), BCD::bcd_to_int(time.day));
  
    // Calculate decimal UTC
    float UTCTime= BCD::bcd_to_int(time.hour) + 0.01666666 * BCD::bcd_to_int(time.minute) + 0.00027777 * BCD::bcd_to_int(time.second); 
    
    // calculate decimal GST and decimal Local Sidereal Time (LST)
    float GST = G + ( dc * nd ) + (tc * UTCTime);           
    float LST = GST + 24.0 + (LONGITUDE / 360 * siderealday);   // adjust for longitude portion of siderail day
    while(LST>24.0) {  LST -= 24.0; }                           // adjust to bring into 0-24 hours
    uint32_t LSTseconds = LST * 3600; // Return LST in Siderial 

    return LSTseconds; 
}


uint32_t nowToSeconds(Clock::time_t &time) {
  uint32_t timeSeconds; 
  
  timeSeconds += BCD::bcd_to_int(time.hour) * 3600; 
  timeSeconds += BCD::bcd_to_int(time.minute) * 60; 
  timeSeconds += BCD::bcd_to_int(time.second) * 1; 
  
  return timeSeconds; 
}


void PrintTimeHuman(long totalDialPeriods, long CurrentIndication) {
    int h, m, s; 
    
    switch (totalDialPeriods) { 
      case 86400: case 43200:
        h = int (CurrentIndication / 3600); 
        m = int ((CurrentIndication - (3600 * (long)h)) / 60); 
        s = CurrentIndication -( 3600 * (long)h) - (60 * (long)m); 
      break; 
    
      case 1440: case 720: 
        h = int (CurrentIndication / 60); 
        m = int (CurrentIndication - (60 * (long)h)); 
        s = 0; 
      break; 
      
    }
    
    Serial.print(h); Serial.print(":"); if (m < 10) Serial.print("0"); Serial.print(m);  
    Serial.print(";"); if (s < 10) Serial.print("0"); Serial.print(s);  
}


// number of days of month (m) and date (d) since beginning of year (y)
int16_t doNumDays(int16_t y, int8_t m, int8_t d) {
  int16_t v=0;
  int8_t leapyear = ((y % 4) == 0)? 1 : 0;
  
  switch(m) {
      case 12:  v += 30;        // Dec
      case 11:  v += 31;        // Nov
      case 10:  v += 30;        // Oct
      case 9:   v += 31;        // Sep
      case 8:   v += 31;        // Aug
      case 7:   v += 30;        // Jul
      case 6:   v += 31;        // Jun
      case 5:   v += 30;        // May
      case 4:   v += 31;        // Apr
      case 3:   v += 28 + leapyear;   // May (if year is leapyear, add extra day after February)
      case 2:   v += 31; break; // Feb
  }
  return v+d;                   // days from Jan 1 of given year
}


namespace Timezone {
    
    uint8_t days_per_month(const Clock::time_t &now) {
        switch (now.month.val) {
            case 0x02:
                // valid till 31.12.2399
                // notice year mod 4 == year & 0x03
                return 28 + ((now.year.val != 0) && ((bcd_to_int(now.year) & 0x03) == 0)? 1: 0);
            case 0x01: case 0x03: case 0x05: case 0x07: case 0x08: case 0x10: case 0x12: return 31;
            case 0x04: case 0x06: case 0x09: case 0x11:                                  return 30;
            default: return 0;
        }
    }

    void adjust(Clock::time_t &time, const int8_t offset) {
        // attention: maximum supported offset is +/- 23h

        int8_t hour = BCD::bcd_to_int(time.hour) + offset;

        if (hour > 23) {
            hour -= 24;
            uint8_t day = BCD::bcd_to_int(time.day) + 1;
            if (day > days_per_month(time)) {
                day = 1;
                uint8_t month = BCD::bcd_to_int(time.month);
                ++month;
                if (month > 12) {
                    month = 1;
                    uint8_t year = BCD::bcd_to_int(time.year);
                    ++year;
                    if (year > 99) {
                        year = 0;
                    }
                    time.year = BCD::int_to_bcd(year);
                }
                time.month = BCD::int_to_bcd(month);
            }
            time.day = BCD::int_to_bcd(day);
            time.weekday.val = time.weekday.val<7 ? time.weekday.val+1 : time.weekday.val-6;
        }

        if (hour < 0) {
            hour += 24;
            uint8_t day = BCD::bcd_to_int(time.day) - 1;
            if (day < 1) {
                uint8_t month = BCD::bcd_to_int(time.month);
                --month;
                if (month < 1) {
                    month = 12;
                    int8_t year = BCD::bcd_to_int(time.year);
                    --year;
                    if (year < 0) {
                        year = 99;
                    }
                    time.year = BCD::int_to_bcd(year);
                }
                time.month = BCD::int_to_bcd(month);
                day = days_per_month(time);
            }
            time.day = BCD::int_to_bcd(day);
            time.weekday.val = time.weekday.val>1 ? time.weekday.val-1 : time.weekday.val+6;
        }

        time.hour = BCD::int_to_bcd(hour);
    }
}


void paddedPrint(BCD::bcd_t n) {
  
    Serial.print(n.digit.hi);
    Serial.print(n.digit.lo);
}


void print_DCF_time(Clock::time_t &now) {
  
   if (now.month.val > 0) {
        switch (DCF77_Clock::get_clock_state()) {
            case Clock::useless: Serial.print(F("useless ")); break;
            case Clock::dirty:   Serial.print(F("dirty:  ")); break;
            case Clock::synced:  Serial.print(F("synced: ")); break;
            case Clock::locked:  Serial.print(F("locked: ")); break;
        }

        switch (now.weekday.val) {
            case 1: Serial.print(F("Monday   ")); break;
            case 2: Serial.print(F("Tuesday  ")); break;
            case 3: Serial.print(F("Wednesday")); break;
            case 4: Serial.print(F("Thursday ")); break;
            case 5: Serial.print(F("Friday   ")); break;
            case 6: Serial.print(F("Saturday ")); break;
            case 7: Serial.print(F("Sunday   ")); break;
        }
        
        Serial.print(F(" 20"));
        paddedPrint(now.year);
        Serial.print('-');
        paddedPrint(now.month);
        Serial.print('-');
        paddedPrint(now.day);
        Serial.print(' ');
        paddedPrint(now.hour);
        Serial.print(':');
        paddedPrint(now.minute);
        Serial.print(':');
        paddedPrint(now.second);

   }
}
