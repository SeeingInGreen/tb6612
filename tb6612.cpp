// tb6612.cpp - A simple library for controlling the Toshiba TB6612FNG motor driver
// This driver assumes that the control lines for each sub-driver are connected, as in the case of the Predator sumo bot
// Christopher Green - 11/4/2016 

// TODO:
// - Add code that can flip motor direction without needing to rewire

#include "tb6612.h"

// Default constructor - does nothing...
tb6612::tb6612(){

}

// Initialization constructor - does the following:
// - Sets up pins
// - Puts motor driver to sleep
tb6612::tb6612(uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin, uint8_t stbyPin){	
	initialize(in1Pin, in2Pin, pwmPin, stbyPin);
}

// Sets pins and does initial driver setup
int tb6612::initialize(uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin, uint8_t stbyPin){
	// Set internal pin reference
	_in1Pin = in1Pin; _in2Pin = in2Pin; _pwmPin = pwmPin; _stbyPin = stbyPin;
	// Initialize pins
	pinMode(in1Pin, OUTPUT);
	pinMode(in2Pin, OUTPUT);
	pinMode(pwmPin, OUTPUT);
	pinMode(stbyPin, OUTPUT);
	
	sleep(); // Put motor driver to sleep
	setDirection(FORWARD);	// Initial direction should be forward
	setSpeed(0);			// Initial speed should be zero
	
	return 0;
}

// Verifies that all pins are configured before trying to control the motor driver
// NOTHING CAN BE CONNECTED TO PIN 0! (This should be the case anyway)
bool tb6612::_check_valid(){
	return (_in1Pin&&_in2Pin&&_pwmPin&&_stbyPin);
}

// Sets motor direction (forward or backward)
int tb6612::setDirection(uint8_t dir){
	if(_check_valid()){
		_direction = dir;
		if(_direction == FORWARD){ // Set CCW
			digitalWrite(_in1Pin, 0);
			digitalWrite(_in2Pin, 1);
		}
		else if (_direction == BACKWARD){ // Set CW
			digitalWrite(_in1Pin, 1);
			digitalWrite(_in2Pin, 0);
		}
		else // Invalid direction
			return -1;
		return 0;
	}
	// Pins not configured?
	else 
		return -2;
}

// Sets speed, 0-255
int tb6612::setSpeed(uint8_t speed){
	if(_check_valid()){
		analogWrite(_pwmPin, speed);
		return 0;
	}
	// Pins not configured?
	else 
		return -2;
}

// Puts driver in standby mode
void tb6612::sleep(){
	if(_check_valid()){
		_sleep = true;
		digitalWrite(_stbyPin, 0); // Standby pin is active low
	}
}

// Wakes driver from standby mode
void tb6612::wake(){
	if(_check_valid()){
		_sleep = false;
		digitalWrite(_stbyPin, 1); // Standby pin is active low
	}
}
