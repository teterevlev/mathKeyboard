#define FROM 1
#define TO 32
#define ADDRESS_OF_MCP23S17_0 0
#define ADDRESS_OF_MCP23S17_1 7
#define PIN_OF_MCP23S17_0 10
#define PIN_OF_MCP23S17_1 10
#define GPIO_SIZE 16
#define SERIAL_SPEED 115200

#include "MCP23S17.h"         // Here is the new class to make using the MCP23S17 easy.
#include <SPI.h>              // We use this library, so it must be called here.

MCP k0(ADDRESS_OF_MCP23S17_0, PIN_OF_MCP23S17_0);
MCP k1(ADDRESS_OF_MCP23S17_1, PIN_OF_MCP23S17_1);


uint32_t despised[TO] = {
	0b10000000000000000000000000000000,
	0b01000000000000000000000000000000,
	0b00100000000000000000000000000000,
	0b00010000000000000000000000000000,
	0b00001000000000000000000000000000,
	0b00000100000000000000000000000000,
	0b00000010000000000000000000000000,
	0b00000001000000000000000000000000,
	0b00000000100000000000000000000000,
	0b00000000010100000000000000000000,
	0b00000000001000000000000000000000,
	0b00000000010100000000000000000000,
	0b00000000000011000000000000000000,
	0b00000000000011000000000000000000,
	0b00000000000000100000000000000000,
	0b00000000000000010000000000000000,
	0b00000000000000001000000000000010,
	0b00000000000000000110000000000001,
	0b00000000000000000110000000000001,
	0b00000000000000000001000000000000,
	0b00000000000000000000100000000000,
	0b00000000000000000000010000000000,
	0b00000000000000000000001000000000,
	0b00000000000000000000000100000000,
	0b00000000000000000000000010010000,
	0b00000000000000000000000001000000,
	0b00000000000000000000000000100000,
	0b00000000000000000000000000010000,
	0b00000000000000000000000000001000,
	0b00000000000000000000000000000100,
	0b00000000000000001000000000000010,
	0b00000000000000000000000000000001 };

bool despite(uint8_t x, uint8_t y){
	if( (despised[x-1] & ( 0b10000000000000000000000000000000 >> (y-1)) ) == 0 ) return true;
	return false;
}
void activatePin(uint8_t pin){
	//Serial.print("\r\Activate: ");
	//Serial.print(pin);
	if(pin<=16){
		k0.pinMode(pin, HIGH);
		k0.digitalWrite(pin, LOW);
	}else{
		uint8_t pin2 = pin-GPIO_SIZE;
		k1.pinMode(pin2, HIGH);
		k1.digitalWrite(pin2, LOW);
	}
}
void activateNextPin(uint8_t pin){
	pin++;
	if(pin > TO){
		pin = 1;
	}
	if(pin<=16){
		k0.pinMode(pin, HIGH);
		k0.digitalWrite(pin, LOW);
	}else{
		uint8_t pin2 = pin-16;
		k1.pinMode(pin2, HIGH);
		k1.digitalWrite(pin2, LOW);
	}
}
void deactivateAllPins(){
	//Serial.print("\r\Deactivate all");
	k0.pinMode(0);
	k0.pullupMode(0xffff);
	k1.pinMode(0);
	k1.pullupMode(0xffff);
}
uint32_t getInputState(){
	uint32_t input = k1.digitalRead();
	input <<= 16;
	input |= k0.digitalRead();
	return input;
}
bool check(uint32_t mask){
	for(uint8_t i=0; i<TO; i++){
		mask>>=1;
	}
}
bool checkBit(uint32_t mask, uint8_t index){
	if(( mask >> (index-1) ) & 1) return true;
	return false;
}
void print(uint8_t i, uint8_t j){
	Serial.print("\r\nRESULT: ");
	Serial.print(i);
	Serial.print(" to ");
	Serial.print(j);
}
void press(uint8_t x, uint8_t y){

}
void cycle(void (*result)(uint8_t, uint8_t)){
	//Serial.print("\r\n");
	//Serial.print(millis());
	for(uint8_t i=FROM; i<=TO; i++){
		
		//activatePin(i);
		uint32_t mask = getInputState();
		deactivateAllPins();
		activateNextPin(i);
		for(uint8_t j=FROM; j<=TO; j++){
			if(despite(i, j)){
				if(checkBit(mask, j) == false){
					result(i, j);
				}
			}
		}


	}
	
}
void calibrate(){
	Serial.print("const uint8_t /*PROGMEM*/ despised[TO][TO] = {\r\n{");
		for(uint8_t i=FROM; i<=TO; i++){
			
			//activatePin(i);
			uint32_t mask = getInputState();
			deactivateAllPins();
			activateNextPin(i);
			for(uint8_t j=FROM; j<=TO; j++){
				if(checkBit(mask, j) == false){
					Serial.print(1);
					}else{
					Serial.print(0);
				}
				if(j<TO) Serial.print(", ");
			}
			if(i<TO) Serial.print("},\r\n{");

		}
	Serial.print("} };\r\n\r\n");
	
}
void calibrateBitwise(){
	Serial.print("const uint32_t /*PROGMEM*/ despised[TO] = {\r\n");
		for(uint8_t i=FROM; i<=TO; i++){
			
			//activatePin(i);
			uint32_t mask = getInputState();
			deactivateAllPins();
			activateNextPin(i);
			
			Serial.print("0b");
			for(uint8_t j=FROM; j<=TO; j++){
				if(checkBit(mask, j) == false){
					Serial.print(1);
				}else{
					Serial.print(0);
				}
			}
			if(i<TO) Serial.print(",\r\n");

		}
	Serial.print(" };\r\n\r\n");
	
}
void setup() {
	Serial.begin(SERIAL_SPEED);
	k0.begin();
	k1.begin();
	deactivateAllPins();
	activatePin(1);
	Serial.println("calibrate");
	calibrateBitwise();
	Serial.println("start");
}
void loop() {
	cycle(print);
}
