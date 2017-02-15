#include "MCP23S17.h"         // Here is the new class to make using the MCP23S17 easy.
#include <SPI.h>              // We use this library, so it must be called here.
#define LED 12
#define FROM 1
#define TO 32

MCP k1(7, 10);             // Instantiate an object called "iochip" on an MCP23S17 device at address 1
MCP k0(0, 10);             // Instantiate an object called "iochip" on an MCP23S17 device at address 1
// and slave-select on Arduino pin 10

void setup() {
	Serial.begin(115200);
	k0.begin();
	k1.begin();
	Serial.println("check");
	deactivateAllPins();
	activatePin(20);
	delay(1000);
	deactivateAllPins();
	Serial.println("start");
}

bool despite(uint8_t x, uint8_t y){
	if(x == y) return false;
	return true;
}
void activatePin(uint8_t pin){
	//Serial.print("\r\Activate: ");
	//Serial.print(pin);
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
	for(uint8_t i=0; i<32; i++){
		mask>>=1;
	}
}
bool checkBit(uint32_t mask, uint8_t index){
	if(( mask >> (index-1) ) & 1) return true;
	return false;
}
void loop() {
	//Serial.print("\r\n");
	//Serial.print(millis());
	for(uint8_t i=FROM; i<=TO; i++){
		
		activatePin(i);
		uint32_t mask = getInputState();
		
		for(uint8_t j=FROM; j<=TO; j++){
			if(despite(i, j)){
				if(checkBit(mask, j) == false){
					print(i, j);
				}
			}
		}


		deactivateAllPins();
	}

}
void print(uint8_t i, uint8_t j){
					Serial.print("\r\nRESULT: ");
					Serial.print(i);
					Serial.print(" to ");
					Serial.print(j);
}