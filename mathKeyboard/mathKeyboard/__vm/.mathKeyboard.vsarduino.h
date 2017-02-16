/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Nano w/ ATmega328, Platform=avr, Package=arduino
*/

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 106012
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define F_CPU 16000000L
#define ARDUINO 106012
#define ARDUINO_AVR_NANO
#define ARDUINO_ARCH_AVR

bool despite(uint8_t x, uint8_t y);
void activatePin(uint8_t pin);
void activateNextPin(uint8_t pin);
void deactivateAllPins();
uint32_t getInputState();
bool check(uint32_t mask);
bool checkBit(uint32_t mask, uint8_t index);
void printPress(uint8_t i, uint8_t j);
void printRelease(uint8_t i, uint8_t j);
bool checkPressFlag(uint8_t x, uint8_t y);
void clearPressFlag(uint8_t x, uint8_t y);
void setPressFlag(uint8_t x, uint8_t y);
void press(uint8_t x, uint8_t y);
void pressDetected(uint8_t x, uint8_t y);
void releaseDetected(uint8_t x, uint8_t y);
void calibrate();
void calibrateBitwise();
//
//

#include "pins_arduino.h" 
#include "arduino.h"
#include "mathKeyboard.ino"
