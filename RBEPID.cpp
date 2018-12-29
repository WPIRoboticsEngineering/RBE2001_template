/*
 * Messages.h
 *
 *  Created on: 10/1/16
 *      Author: joest
 */
#include "Arduino.h"
#include "RBEPID.h"

//Class constructor
RBEPID::RBEPID() {
	kp = 1;
	ki = 0;
	kd = 0;
}

//Function to set PID gain values
void RBEPID::setpid(float P, float I, float D) {
	kp = P;
	ki = I;
	kd = D;
}

//Write this function to calculate a control signal from the set point
//and the current position
float RBEPID::calc(double set, double cur) {

	// calculate error
	float err = set - cur;
	// calculate derivative of error
	//TODO
	// calculate integral error. Running average is best but hard to implement
	//TODO
	// sum up the error value to send to the motor based off gain values.
	//TODO

	float out = err * kp;	// simple P controller
	//return the control signal from -1 to 1
	if (out > 1)
		out = 1;
	if (out < -1)
		out = -1;
	return 0;
}

// Clear the integral accumulator
void RBEPID::clearIntegralBuffer() {
	//TODO
}
