
#include "Arduino.h" 
#include "Dial.h"

Dial::Dial(int PinA, int PinB, int Pulsems, int timeType, int dialType) {
  pinMode(PinA, OUTPUT); 
  pinMode(PinB, OUTPUT); 

  // Save public variables to private variables for use in other Dial functions
  _pinA = PinA; 
  _pinB = PinB; 
  _timeType = timeType; 
  _dialType = dialType; 
  _pulsems = Pulsems; 
  
  switch (dialType) {
    case MINUTE12:   
      _totalDialPeriods = 720;   
      switch (timeType) {
        
        case LOCAL: case UTC: 
          _periodms = 60000; 
          _pauseDefaultms = 60000 - _pulsems; 
        break; 
        case SIDERIAL:
          _periodms =  59820.2695;
          _pauseDefaultms = (int)_periodms - _pulsems;
        break; 
      }
    break; 
    
    case MINUTE24:   
      _totalDialPeriods = 1440;   
      switch (timeType) {
        case LOCAL: case UTC: 
          _periodms =  60000;
          _pauseDefaultms = (int)_periodms - _pulsems; 
        break; 
        case SIDERIAL:
          _periodms =  59820.2695; 
          _pauseDefaultms = (int)_periodms - _pulsems;
        break; 
      }
    break; 
    
    case SEC12:      
      _totalDialPeriods = 43200;  
      switch (timeType) {
        case LOCAL: case UTC: 
          _periodms =  1000; 
          _pauseDefaultms = (int)_periodms - _pulsems;
        break; 
        case SIDERIAL:
          _periodms =  997.2695; 
          _pauseDefaultms = (int)_periodms - _pulsems;
        break; 
      }
    break; 
    
    case SEC24:      
      _totalDialPeriods = 86400;  
      switch (timeType) {
        case LOCAL: case UTC: 
          _periodms =  1000; 
          _pauseDefaultms = (int)_periodms - _pulsems;
        break; 
        case SIDERIAL:
          _periodms =  997.2695; 
          _pauseDefaultms = (int)_periodms - _pulsems; 
        break; 
      }
    break; 
  }
  _maxTicks = pow(2, 32) / (int)_periodms;  // avoid rollover of millisForTicks
}; 


void Dial::SetDial (char rx_bytes[]) {
   long toSet = 0; 
   toSet += (rx_bytes[1] - '0') * 36000; 
   toSet += (rx_bytes[2] - '0') * 3600; 
   toSet += (rx_bytes[3] - '0') * 600 ; 
   toSet += (rx_bytes[4] - '0') * 60; 
   toSet += (rx_bytes[5] - '0') * 10; 
   toSet += (rx_bytes[6] - '0') * 1; 
   
   switch (_totalDialPeriods) { 
     case 86400: case 43200:
      _CurrentIndication = toSet;      // set in seconden
     break; 
     case 1440: case 720: 
      _CurrentIndication = toSet / 60; // set in minuten
     break; 
   }
}


void Dial::WriteEEPROM(int address) {
  EEPROM.write(address,_state); 
  EEPROM_writeAnything(address + 1,_CurrentIndication);  
}


void Dial::ReadEEPROM(int address) {
  _state = EEPROM.read(address); 
  EEPROM_readAnything(address + 1, _CurrentIndication);  
}


void Dial::DoCorrection () {
  switch (DCF77_Clock::get_clock_state()) {
    case Clock::useless: case Clock::dirty: 
      dcf77_monitor_led = dcf77_monitor_led_red;  
      digitalWrite (dcf77_monitor_led_green,0);       // Turn off green led if this was on
      DoFractional (); 
    break;
    
    case Clock::synced:  case Clock::locked:  
      dcf77_monitor_led = dcf77_monitor_led_green; 
      digitalWrite (dcf77_monitor_led_red,0);       // Turn off red led if this was on
      DoDCF(); 
    break;     
  }
}


void Dial::DoFractional () { 
  if (_ticks <1) return; 

  if (_ticks > _maxTicks) {         // avoid rollover
    _ticks = 0; 
    _millisecondsForTicks = 0; 
#ifdef DB_SERIAL_TICK
    Serial.print("ResetMaxTicks");
#endif
  }
  
  if (_ticks > _oldTicks ) {
#ifdef DB_SERIAL_TICK
    Serial.print ("_ticks: "); Serial.println (_ticks); 
#endif    
    realPeriod = (float) _millisecondsForTicks / (float)_ticks; 
    
    if (realPeriod < (int)_periodms) {
      _ticks = 0; 
      _millisecondsForTicks = 0;  // restart if offscale. 
    }
#ifdef DB_SERIAL_TICK    
    Serial.print ("Period: "); Serial.print(_periodms); Serial.print (" RealPeriod: ");Serial.println (realPeriod,4); 
#endif
    
    if (realPeriod < _periodms) {
      _correction = 1; 
    } else {
      _correction = 0; 
    }
#ifdef DB_SERIAL_TICK    
    Serial.print ("_correction: "); Serial.println (_correction); 
#endif
    _oldTicks = _ticks; 

  }
}


void Dial::DoDCF() {
  long realtime, offset; 
  
  Clock::time_t now;
  DCF77_Clock::read_current_time(now);
  Timezone::adjust(now, (now.uses_summertime? -2: -1)); // Subtrackt MET/MEST offset from DCF to find UTC
  
  switch (_timeType) {
    
    case UTC: 
      realtime = nowToSeconds(now); 
    break; 
    
    case LOCAL: 
      Timezone::adjust(now, timezone_offset + (timezone_DST? (now.uses_summertime? 1:0):0));
      realtime = nowToSeconds(now); 
    break; 
    
    case SIDERIAL: 
      Timezone::adjust(now, (now.uses_summertime? -2: -1)); // Subtrackt MET/MEST offset from DCF to find UTC
      realtime = currentSiderealSecond(now); 
    break; 
    
  }
  
  switch (_dialType) {
    
    case MINUTE12: 
      realtime /= 2; 
     
    case MINUTE24: 
      realtime /= 60; 
      
      offset = _CurrentIndication - realtime; 
      if (offset > _totalDialPeriods / 2)   offset -= _totalDialPeriods; 
      if (offset < _totalDialPeriods / -2)  offset += _totalDialPeriods; // Want de klok is rond.. 
      
      if (offset == 0) _correction = 0; 
      if (offset < -1 && offset > -6) _correction = -10000;   // speed 10 s up when less than 6 minutes behind
      if (offset > 1 && offset < 6) _correction = 1000000L;   // Stop when less than 6 minutes ahead
      if (offset > 6 || offset < -6) _correction = -59000;    // Speed up. 
      
    break;
       
    case SEC12: 
      realtime /= 2; 
    
    case SEC24:
    
      offset = _CurrentIndication - realtime; 
      if (offset > _totalDialPeriods / 2)   offset -= _totalDialPeriods; 
      if (offset < _totalDialPeriods / -2)  offset += _totalDialPeriods; 

      if (offset == 0) _correction = 0; 
      if (offset < -1 && offset > -360) _correction = -100;     // speed 0,1 s up when less than 6 minutes behind
      if (offset > 1 && offset < 360) _correction = 100;        // speed 0,1 s down when less than 6 minutes ahead
      if (offset > 360 || offset < -360) _correction = 59000;   // One pulse per minute, (almost) stop and wait. 
    break; 
    
  }
}


uint8_t Dial::RunStop(uint8_t runStop) { 
  _runStop = runStop; 
  return runStop; 
}


void Dial::DialSR()   // Dial service routine. runStop = TRUE = run, runStop = FALSE = stop
{ 
  _millisecondsForTicks++; 
  if ((milliseconds - _lastMilliseconds) < _delayTime ) {   
    return; 
  }

  _lastMilliseconds = milliseconds; 
  
  // Serial.print ("_tickCorrection: "); Serial.println (_tickCorrection); 
     
  switch (_state) {  
    case 0: //   pause

      // if (_correction != 0 ) DialPrintIndication(); // for debug 
      
      digitalWrite (_pinA,0); 
      digitalWrite (_pinB,0); 
      
      _delayTime =  
        _pauseDefaultms + 
        _correction;
        
      if (_runStop) _state = 1;
    break;  
    
    case 1: // pulse A 
      digitalWrite (_pinA,1); 
      digitalWrite (_pinB,0); 
      _CurrentIndication++; 
      _ticks++;
      
      _delayTime = _pulsems; 
      
      _state = 2; 
    break; 
    
    case 2: //  pause 
      digitalWrite (_pinA,0); 
      digitalWrite (_pinB,0); 
      
      _delayTime =  
        _pauseDefaultms + 
        _correction;
         
       if (_runStop) _state = 3;                     
    break; 

    case 3: // pulse B
      digitalWrite (_pinA,0); 
      digitalWrite (_pinB,1); 
      _CurrentIndication++; 
      _ticks++;
      
      _delayTime = _pulsems; 
      
      _state = 0; 
    break; 
  }

   // Serial.print("_delayTime   "); Serial.println(_delayTime); 
   // Serial.print("milliseconds "); Serial.println(milliseconds); 
  
  if (_CurrentIndication > _totalDialPeriods) _CurrentIndication = 0; 
  
  return; 
}

void Dial::DialPrintIndication() {
  Serial.print("Type: "); 
  switch (_dialType) {
    case MINUTE12:    Serial.print("12h, minutes,"); break; 
    case MINUTE24:    Serial.print("24h, minutes,"); break; 
    case SEC12:       Serial.print("12h, seconds,"); break; 
    case SEC24:       Serial.print("24h, seconds,"); break; 
  }
  switch (_timeType) {
    case SIDERIAL:  Serial.print(" siderial. "); break; 
    case LOCAL:     Serial.print(" lokal.    "); break; 
    case UTC:       Serial.print(" UTC.      "); break; 
  }
  Serial.print("Position: "); 
  
  PrintTimeHuman (_totalDialPeriods, _CurrentIndication); 
  Serial.print(" correction: "); Serial.print(_correction); Serial.print(" ms/impuls");
  Serial.println();  
}
