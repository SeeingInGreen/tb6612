// tb6612.h - A simple library for controlling the Toshiba TB6612FNG motor driver
// This driver assumes that the control lines for each sub-driver are connected, as in the case of the Predator sumo bot
// Christopher Green - 11/4/2016 

#include "Arduino.h"
#include <stdint.h>

#define FORWARD 1 // CCW
#define BACKWARD 0 // CW

class tb6612{
public:
	tb6612(); //
	tb6612(uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin, uint8_t stbyPin); // Initialize with parameters
	int initialize(uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin, uint8_t stbyPin); // Sets the internal values for the driver class
	bool _check_valid(); // Verifies that the driver is properly configured before taking any action
	
	// Control functions, return 0 if no error
	int setDirection(uint8_t dir);	// Sets motor direction (forward or backward)
	int setSpeed(uint8_t speed); // Sets speed, 0-255
	void sleep(); // Puts driver in standby mode, 
	void wake(); // Wakes driver from standby mode
	
private:
	// Pin Number Definitions
	uint8_t _in1Pin, _in2Pin, _pwmPin, _stbyPin; // Direction control 1, 2, speed control, standby
	uint8_t _direction = FORWARD;
	uint8_t _speed = 0;
	bool _sleep = false;
	
};