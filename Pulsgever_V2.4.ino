/*
  Siderial clock impulse

  Aart for WLS, 09-2019

  Based on the DCF library and example by:
  www.blinkenlight.net, Copyright 2016 Udo Klein, GPL

  Siderial time routine adapted from:
  https://langster1980.blogspot.com/2015/11/arduino-sidereal-clock-using-gps-module.html

  Serial setting: 115200 baud

  Dial object based on klokpulsgever_1.3

  Todo: - Test with minute dial

  
  
*/

// VERSION
#define VERSION 2.4                 // As reported on serial connection.   

// Debug flags. Normal function of C2 is Green led
// #define DB_PULSE_INTERRUPT       // C2 high during 1ms interrupt activity. disables normal led function. 14 us with one dial, 17 with two.
// #define DB_PULSE_DIALS           // C2 high during DoCorrection() of all dials. 12 us when running fractional, 350 us when locked to DCF
// #define DB_SERIAL_TICK           // Sends Period, Realperiod, Correction variables per tick over serial. Use only with one dial.
// #define DB_POWER                 // Sends info about the power detection
#define MILLS_TYPE uint32_t         // can be set from uint32_t to to uint16_t for overflow testing of milliseconds in 65 seconds. 

// Includes
#include <EEPROM.h>
#include <dcf77.h>
#include "Dial.h"

// Constants
// Time type
const uint8_t LOCAL     = 1;
const uint8_t SIDERIAL  = 2;
const uint8_t UTC       = 3;

// Dial type
const uint8_t SEC24    = 1;   // 24h dial seconds impulse
const uint8_t MINUTE24 = 2;   // 24h dial minute impulse
const uint8_t SEC12    = 3;   // 12h dial seconds impulse
const uint8_t MINUTE12 = 4;   // 12h dial minute impulse

// *** USER SETTINGS *** 

// #define SECONDARY_DIAL        // Comment out when using one dial or during debugging. 

// Lokal Offset to UTC.
const int8_t timezone_offset = 1;  // Leiden (Amsterdam) = +1
const uint8_t timezone_DST = 1;      // Local timezone uses daylight saving time

// Longitude for calculation of siderial time
const float LONGITUDE = 4.463; // 4.463 home, 4.483 Observatory

// Dial (PinA, PinB, Pulsems, timeType, dialType )
// Pin A and pin B are the inputs of the H-bridge for the coil of the clock.
// Pulsems is the length of the pulses in ms.

Dial dial1 (9,  10,  300,  LOCAL,  SEC24);

#ifdef SECONDARY_DIAL
  Dial dial2 (3,  11,  300,  LOCAL,     SEC24);
#endif

const uint16_t LAMP_AUTO_OFF = 3600; // 3600 s = 1 h

// *** END OF USER SETTINGS ****

// pins Switches and lamps 
const uint8_t LAMP1   = 5;
const uint8_t SWITCH1 = 2;
const uint8_t LAMP2   = 6;
const uint8_t SWITCH2 = 4;

// Voltage measurement / power detect settins
#define USENSE A0                   // 1:10 Voltage divider to raw DC bus 
const int U_UNDER = 500;            // adc ticks for loss of power detect. About 16V
const int U_RETURN = 600;           // adc ticks for return of power detect. About 22V
const MILLS_TYPE U_TIME = 3;        // ms between power checks 
const uint8_t U_LOSS_COUNTER = 10;      // amount of times the checked USENSE was under U_UNDER before loss of power is detected. Nessesary because a pulsating DC is measured

// DCF Hardware & monitor led. 
const uint8_t dcf77_sample_pin = 8;                 // = B5
const uint8_t dcf77_monitor_led_red = 16;           // = C2
const uint8_t dcf77_monitor_led_green = 17;         // = C3
int dcf77_monitor_led = dcf77_monitor_led_red;      // Global variable for led color to keep interrupt as short as possible

// Dependand on receiver module:
const uint8_t dcf77_inverted_samples = 0;
const uint8_t dcf77_pin_mode = INPUT_PULLUP;  // enable internal pull up

// *** END OF SETTINGS

// Global milliseconds counter
volatile MILLS_TYPE milliseconds = 0;          // Montone counter. Only counting up to avoid rollover problems.

// EEPROM addresses
const uint8_t FLAG_EEPROM = 0;
const uint8_t DIAL1EEPROM = 1;
const uint8_t DIAL2EEPROM = 10;
const uint8_t COUNTER = 30;

// Necessary declaration
namespace Timezone {
  void adjust(Clock::time_t &time, const int8_t offset);
}


// DCF hardware sampling routine. Also 1ms interrupt for counting millseconds and running dials.
uint8_t sample_input_pin() {
  
  #ifdef DB_PULSE_INTERRUPT
    digitalWrite(A2, HIGH);
  #endif
  
  const uint8_t sampled_data = dcf77_inverted_samples ^ digitalRead(dcf77_sample_pin);
  
  #ifndef DB_PULSE_DIALS
    #ifndef DB_PULSE_INTERRUPT
      digitalWrite(dcf77_monitor_led, sampled_data);
    #endif
  #endif

  milliseconds++;

  dial1.DialSR();
  #ifdef SECONDARY_DIAL
    dial2.DialSR();
  #endif
  
  #ifdef DB_PULSE_INTERRUPT
    digitalWrite(A2, LOW);
  #endif
  
  return sampled_data;
}


// EEPROM functions for storing readouts
// Source of these functions: https://playground.arduino.cc/Code/EEPROMWriteAnything/`
template <class T> int EEPROM_writeAnything(int ee, const T& value) {
  
  const byte* p = (const byte*)(const void*)&value;
  unsigned int i;
  
  for (i = 0; i < sizeof(value); i++)
    EEPROM.write(ee++, *p++);
  return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value) {
  
  byte* p = (byte*)(void*)&value;
  unsigned int i;
  
  for (i = 0; i < sizeof(value); i++)
    *p++ = EEPROM.read(ee++);
  return i;
}


// Check for power loss and act
void powerCheck(void) {
  static MILLS_TYPE lastMilliseconds;
  static int uLossCounter = 0; 

  if ((milliseconds - lastMilliseconds) < U_TIME) { // once in U_TIME ms
    return; 
  }

  lastMilliseconds = milliseconds;
   
  int usense = analogRead(USENSE);
  
  if (usense < U_UNDER) {              
    uLossCounter++; 

    #ifdef DB_POWER    
      if (uLossCounter > 2) {
        Serial.print("u loss counter: "); Serial.println (uLossCounter); // debugging
        Serial.print("u sense: "); Serial.println (usense); // debugging
        Serial.print("Millis: "); Serial.println (milliseconds); // debugging 
        Serial.println(" "); 
      }  
    #endif
    
    if (uLossCounter < U_LOSS_COUNTER) { 
      return; 
    }

    Serial.println("Loss of power ! ");         
  
    dial1.WriteEEPROM(DIAL1EEPROM);
    #ifdef SECONDARY_DIAL
      dial2.WriteEEPROM(DIAL2EEPROM);
    #endif

    EEPROM.write(FLAG_EEPROM, true); // Flag data is stored
    Serial.println("Dial positions stored in EEPROM");

    dial1.RunStop(0);
    #ifdef SECONDARY_DIAL
      dial2.RunStop(0);
    #endif

    while ( usense < U_RETURN) {
      // Wait here for possible return of power or restart
      usense = analogRead(USENSE);
    }
    Serial.println("Return of power before shutdown. ");
        
    dial1.RunStop(1);
    #ifdef SECONDARY_DIAL
      dial2.RunStop(1);
    #endif
    
    EEPROM.write(FLAG_EEPROM, false); // unflag
  } else {
    uLossCounter = 0; 
    
  }
}


void control_lamps(void) { // both lamps are controlled by the button on SWITCH1
  static int lamp;
  static MILLS_TYPE lastLamp;
  
  switch (lamp) {
    case 0:
      // lamp off
      digitalWrite (LAMP1, LOW);
      digitalWrite (LAMP2, LOW);
      
      if (milliseconds - lastLamp > 1000 && digitalRead(SWITCH1) == LOW) {
        lamp = 1;
        lastLamp = milliseconds;
        Serial.println("Lamp on.");
      }
      break;

    case 1:
      // lamp on
      digitalWrite (LAMP1, HIGH);
      digitalWrite (LAMP2, HIGH);
      
      if (milliseconds - lastLamp > 1000 && digitalRead(SWITCH1) == LOW) {
        lamp = 0;
        lastLamp = milliseconds;
        Serial.println("Lamp off.");
      }

      // Auto off
      if  (milliseconds - lastLamp > 1000 * LAMP_AUTO_OFF) {   // LAMP_AUTO_OFF in s
        lamp = 0;
        Serial.println("Lamp turned off by timer.");
      }
      break;
  }
}

void setup() { // Do once
  int startUpCounter;
  
  Serial.begin(115200);
  Serial.println();

  pinMode(dcf77_monitor_led, OUTPUT);
  pinMode(dcf77_sample_pin, dcf77_pin_mode);

  pinMode(LAMP1, OUTPUT);
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(LAMP2, OUTPUT);
  pinMode(SWITCH2, INPUT_PULLUP);

  pinMode(USENSE, INPUT);
  analogReference(DEFAULT);

  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);  

  if (EEPROM.read(FLAG_EEPROM) == true) {

    dial1.ReadEEPROM(DIAL1EEPROM);
    #ifdef SECONDARY_DIAL
      dial2.ReadEEPROM(DIAL2EEPROM);
    #endif

    // Start-up counter:
    EEPROM_readAnything(COUNTER, startUpCounter);
    startUpCounter++;
    EEPROM_writeAnything(COUNTER, startUpCounter);

    EEPROM.write(FLAG_EEPROM, false); // unflag

    Serial.println("Previous dial positions read.");

  } else {
    Serial.println("Dial positions unknown.");
  }

  DCF77_Clock::setup();
  DCF77_Clock::set_input_provider(sample_input_pin);

}


// main loop, run continuosly. The DCF decoding and processing library runs "invisibly" in the timer interrupt, as does the impulses
void loop() {

  // Check for power failure
  powerCheck();

  // Handle the serial command terminal
  Check_serial_input();
  
  // Control lamps
  control_lamps();

  // Correct dials pulses. This to get fractional ms in the running OR DCF sync.
  #ifdef DB_PULSE_DIALS
    digitalWrite(A2, HIGH);
  #endif
  dial1.DoCorrection();

  #ifdef SECONDARY_DIAL
    dial2.DoCorrection();
  #endif
  #ifdef DB_PULSE_DIALS
    digitalWrite(A2, LOW);
  #endif
  
}
