
void Check_serial_input(void) {
  static uint8_t rx_count; 
  static char rx_bytes[10]; 
  
  if (Serial.available() > 0) { 
    char rx_byte = Serial.read(); 
    rx_bytes[rx_count] = rx_byte;
    rx_count++; if (rx_count>9) rx_count = 0; 
    if (rx_byte == '\r' || rx_byte == '\n') {
      process_command(rx_bytes); 
      while (Serial.available()) Serial.read(); 
      rx_count = 0; 
    }
  }
}


void process_command(char rx_bytes[]) {
  int counter; 
  
  while (rx_bytes[counter] != '\r' && rx_bytes[counter] != '\n') { 
    Serial.print(rx_bytes[counter]); 
    counter++; 
  }
  
  Serial.println(" ");
  
  switch (rx_bytes[0]) {
    case '\r':
      print_status(); 
    break; 
    case '1':
      dial1.SetDial(rx_bytes); 
      print_status(); 
    break; 
    #ifdef SECONDARY_DIAL
      case '2':
        dial2.SetDial(rx_bytes); 
        print_status(); 
      break;
    #endif
   
  }
  Serial.println(); Serial.print("> ");
}


void print_status() {
  int startUpCounter; 
  EEPROM_readAnything(COUNTER, startUpCounter);
  
  Serial.println();
  Serial.print("Klok impuls gever "); Serial.print(VERSION); Serial.println(" WLS, Aart 2019");
  Serial.println("Status: ");
  Serial.println(); 
  
  Serial.print(startUpCounter); Serial.println(" times restarted");  
  Serial.println();
  Serial.print("Longitude: "); Serial.println(LONGITUDE); 
  Serial.println(); 
  
  Serial.print("UTC time:       "); 
  
  if (DCF77_Clock::get_clock_state() != Clock::useless) {
    
    Clock::time_t now;
    DCF77_Clock::read_current_time(now);
    Timezone::adjust(now, (now.uses_summertime? -2: -1)); // Subtrackt MET/MEST offset from DCF to find UTC
    print_DCF_time(now); Serial.println(" "); 

    Serial.print("Local siderial: "); 
    long sid = currentSiderealSecond(now); 
    PrintTimeHuman(86400, sid);
    Serial.println(" "); 

    Timezone::adjust(now, timezone_offset + (timezone_DST? (now.uses_summertime? 1:0):0)); // Find lokal time

    Serial.print("Local time:     "); 
    print_DCF_time(now); 
    int8_t offset_to_utc = timezone_offset + (timezone_DST? (now.uses_summertime? 1:0):0);
    Serial.print(F(" UTC"));
    Serial.print(offset_to_utc<0? '-':'+');
    if (abs(offset_to_utc) < 10) {
        Serial.print('0');
    }
    Serial.println(abs(offset_to_utc));
    
  } else {
    Serial.print(" unset.");
  }
  Serial.println();
  Serial.println();  
  Serial.print("Dial 1: "); dial1.DialPrintIndication();  
  #ifdef SECONDARY_DIAL 
    Serial.print("Dial 2: "); dial2.DialPrintIndication();
  #endif   
  Serial.println(); 
  Serial.println("To set dial 1: 1hhmmss, dial 2: 2hhmmss"); 

}
