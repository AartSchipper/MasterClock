MasterClock
===========

Arduino based master clock for slave clocks. 
--------------------------------------------

* Minute or second impulses. 
* DCF-77 as a time reference. 
* Siderial, lockal or UTC time. 

This is an Arduino project that runs up to two (sets of-) slave clocks showing different types of time. It was created for the 24h second impulse clocks of the Old Leiden Observatory. 

The project consists of specially created hardware, akin to an Arduino Uno with an xtal and some interfaces, and an Arduino based firmware. The firmware is based on the DCF library and examples by: https://github.com/udoklein/dcf77, Copyright 2016 Udo Klein, GPL

Aart, 04-2020


Hardware layout
---------------

The hardware consists of an low-current 24V H-bridge per clock, the processor, a DCF receiver, a power supply and some auxilary circuits. 

A red/green duo led shows the DCF pulses and if the clock is currently synced to dcf. An extra provision is made to power and switch the lamps (24V / 12W) in the clock dials. Care was taken to use only lineair regulators and just one lighly loaded electrolitic capacitor for longelivity. The regulators are mounted on the aluminium base for cooling. 

The firmware should run on almost any Arduino compatible hardware _with a crystal_. A resonator might cause problems with the DCF library, see: https://github.com/udoklein/dcf77 

There is a standard six pin UART interface both for programming using the bootloader, and setting using a terminal. There is a jumper to disable the reset of the uC, to avoid nuisance resets in normal use. 

A known omission in the current hardware is a pull-down resistor on the gate of the MOSFET for the lights. 

The design was made in KiCad. Gerbers and a PDF of the circuits are provided.  


Firmware layout
---------------

The Dial class contains all functions related to a dial. 
dail1 & dail2 are instances of this class. 

Every millisecond sample_input_pin() is called by the DCF library.   
In this routine also Dial::DialSR(), the dial Service Routine is called to see if a puls needs to be started or stopped.   

The rest of the program runs in the main loop and is not time critical. In this loop: 
* powerCheck() stops the dails in case of power loss and stores the positions in EEPROM, so the clocks can continue automatically when power returns. 
* Check_serial_input() Handles the terminal for debugging and synchonizing the dials. 
* Dial::DoCorrection() Handles synchronising the dials to DCF, or running the dial at the correct rate in case the DCF signal is lost. 

Terminal
--------

The firmware has a simple provision for reading the time and setting the current position of the hands on the dials using the terminal:

---

Klok impuls gever 2.40 WLS, Aart 2020
> Status: 

> 109 times restarted

>Longitude: 4.46

> UTC time:       synced: Monday    2020-04-13 10:51:17 
> Local siderial: 0:37;26 
> Local time:     synced: Monday    2020-04-13 12:51:17 UTC+02


> Dial 1: Type: 24h, seconds, siderial. Position: 0:37;26 correction: 0 ms/impuls

> To set dial 1: 1hhmmss, dial 2: 2hhmmss


---

Dial type, time type and Longitude are all compile time settings. If the dial positions are not set 0:00;00 is assumed at first startup. 


Typical behaviour
-----------------

Assuming the dail positions were correct during shutdown: 
* After startup the dials run in the default speed of the time type until the DCF library is synced.  
* When the library is synced the led turns green and the hands are moved to the correct position (minute impulse dials) or stopped (second impulse dials) to wait until the correct time to start. 

Small deviations up to six minutes are corrected by making the pauses between impulses slightly longer or shorter. 





 


