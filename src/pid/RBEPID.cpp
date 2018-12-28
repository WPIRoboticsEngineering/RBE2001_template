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
	kp = 0;
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

	// calculate derivative of error

	// calculate integral error. Running average is best but hard to implement

	// sum up the error value to send to the motor based off gain values.


	//return the control signal from -1 to 1
	return 0;
}

// Clear the integral accumulator
void RBEPID::clearIntegralBuffer(){

}
