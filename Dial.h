/*
 *  Dial library
 */

#ifndef DIAL_H
#define DIAL_H

#include "Arduino.h" 

class Dial 
{
  public: 
    // constructor:
    Dial(int PinA, int PinB, int Pulsems, int timeType, int dialType); 

    // Public functions: 
    void DialSR(void);                // Dial service routine. Next timestamp () in ms. 
    uint8_t RunStop(uint8_t);         // Set or get Run / Stop 
    
    void DialPrintIndication(void);   // Print indicated time
    void SetDial(char[8]);            // Set dial at hhmmss 
    void DoCorrection (void);         // Correct dial. Also set led color. 
    
    void WriteEEPROM(int address);    // Write dial position to EEPROM
    void ReadEEPROM(int address);     // Read previous dial position from EEPROM
    
  private: 
    // Store properties: 
    unsigned int _pinA, _pinB, _timeType, _dialType;

    // inwendige
    float _periodms;                // Ideal period of this dial type in ms. 
    long _totalDialPeriods, _CurrentIndication, _correction; 
    uint8_t _state = 1, _runStop = 1; 
    uint16_t _pulsems, _pauseDefaultms;  
    MILLS_TYPE _delayTime,_lastMilliseconds;      
    
    uint32_t _ticks = 0, _oldTicks, _maxTicks, _millisecondsForTicks; 
    float realPeriod;
    
    // Functions
    void DoDCF(void);               // Sync with DCF
    void DoFractional(void);        // Check for extra fractional ms if there is no DCF
  
};

#endif
