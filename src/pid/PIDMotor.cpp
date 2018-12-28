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
	Vel=0;
	prevTime=0;
}

PIDMotor::~PIDMotor() {
	// TODO Auto-generated destructor stub
}
void PIDMotor::pidinit() {
//	myPID.SetMode(MANUAL);
//	myPID.SetMode(AUTOMATIC);
//	myPID.SetOutputLimits(-PID_OUTPUT_COMPUTE_RANGE, PID_OUTPUT_COMPUTE_RANGE);
//	myPID.SetTunings(Kp, Ki, Kd, P_ON_E);
//	myPID.SetSampleTime(5);
}

void PIDMotor::loop() {
	if(millis()-lastTimeRunPID>myPID.sampleRateMs){
		lastTimeRunPID=millis();
	}else{
		return;
	}
	Input = (float) getPosition();
	bool thisErrPositive = Input > 0;
	if (thisErrPositive != lastErrPositive) {
		myPID.clearIntegralBuffer();
	}
	lastErrPositive = thisErrPositive;
	Output = myPID.calc(Setpoint, Input);
	if (Output == 0.0) {
		setOutput(getOutputStop());
		return;
	}
	if (Output > 1.0) {
		setOutput(getOutputMax());
		return;
	}
	if (Output < -1.0) {
		setOutput(getOutputMin());
		return;
	}
	float out;
	if (Output > 0)
		out = myFmap(Output, 0,
		1, getOutputStop()+getOutputMaxDeadbad(), getOutputMax());
	else
		out = myFmap(Output, -1,
		0, getOutputMin(),getOutputStop()-getOutputMinDeadbad());
	setOutput(out);

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
	if (timeInterval < 100)
		return Vel;		// If this is polled too fast, return the cached time
	//encoder ticks since last call
	movement = curPos - prevPos;
	//encoder ticks to degrees
	movement = movement * ticksToDeg;
	//timeInterval in seconds
	timeInterval = timeInterval / 1000;
	//Velocity in degrees per milliseconds
	Vel = movement / timeInterval;
	//sets curent vals to previous
	prevPos = curPos;
	prevTime = curTime;
	return Vel;
}
