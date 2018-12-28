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

//Write this function to calculate a control signal from the set velocity 
//and the current velocity 
float RBEPID::calc(double setVel, double curVel) {

	// calculate error

	// calculate derivative of error

	// calculate integral error. Running average is best but hard to implement

	// sum up the error value to send to the motor based off gain values.

	// limit control value to 0-254

	//return the control signal
	return 0;
}
