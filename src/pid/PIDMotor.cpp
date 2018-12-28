/*
 * PIDMotor.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: hephaestus
 */

#include "PIDMotor.h"
#include <Arduino.h>

float myFmap(float x, float in_min, float in_max, float out_min,
		float out_max) {

	return ((x - in_min) * (out_max - out_min) / (in_max - in_min)) + out_min;
}

PIDMotor::PIDMotor() {
	Vel = 0;
	prevTime = 0;
}

PIDMotor::~PIDMotor() {
	// TODO Auto-generated destructor stub
}
void PIDMotor::pidinit() {

}

void PIDMotor::loop() {
	if (millis() - lastTimeRunPID > myPID.sampleRateMs) {
		lastTimeRunPID = millis();
	} else {
		return;
	}
	Input = (float) getPosition();
	bool thisErrPositive = Input > 0;
	if (thisErrPositive != lastErrPositive) {
		myPID.clearIntegralBuffer();
	}
	lastErrPositive = thisErrPositive;
	Output = myPID.calc(Setpoint, Input);
	setOutputUnitVector(Output) ;
	calcVel();// ensure the velocity value is kept up to date
}
// Set the output using a -1 to 1 unit vector.
// Zero is stop
void PIDMotor::setOutputUnitVector(float out) {
	Output = out;
	hardwareOutput = getOutputStop();
	if (Output == 0.0) {
		hardwareOutput = getOutputStop();
	} else if (Output > 1.0) {
		hardwareOutput = getOutputMax();
	} else if (Output < -1.0) {
		hardwareOutput = getOutputMin();
	} else {
		if (Output > 0)
			hardwareOutput = myFmap(Output, 0, 1,
					getOutputStop() + getOutputMaxDeadbad(), getOutputMax());
		else
			hardwareOutput = myFmap(Output, -1, 0, getOutputMin(),
					getOutputStop() - getOutputMinDeadbad());
	}
	setOutput(hardwareOutput);
}
void PIDMotor::overrideCurrentPosition(int64_t val) {
	overrideCurrentPositionHardware(val);

	setSetpoint(val);
	myPID.setpid(Kp, Ki, Kd);
	myPID.clearIntegralBuffer();
}
void PIDMotor::setSetpoint(int64_t val) {
	Setpoint = (float) val;
}
float PIDMotor::getSetPoint() {
	return Setpoint;
}
void PIDMotor::SetTunings(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	overrideCurrentPosition(getPosition());
}



// Returns Vel in degress/second
double PIDMotor::calcVel() {
	//current positions
	double curPos = getPosition();
	//current time
	curTime = millis();
	//time change in ms from last call
	timeInterval = curTime - prevTime;
	if (timeInterval < 20)
		return Vel;		// If this is polled too fast, return the cached velocity
	//encoder ticks since last call
	movement = curPos - prevPos;
	//encoder ticks to degrees
	movement = movement * ticksToDeg();
	//timeInterval in seconds
	timeInterval = timeInterval / 1000;
	//Velocity in degrees per milliseconds
	Vel = movement / timeInterval;
	//sets curent vals to previous
	prevPos = curPos;
	prevTime = curTime;
	return Vel;
}
