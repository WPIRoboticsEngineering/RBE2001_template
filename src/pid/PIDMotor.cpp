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
	myPID.clearIntegralBuffer();
}

void PIDMotor::loop() {
	if (millis() - lastTimeRunPID > myPID.sampleRateMs) {
		lastTimeRunPID = millis();
	} else {
		return;
	}
	// Perform linear/sinusoidal interpolation
	float interpElapsed = (float) (millis() - startTime);
	if (interpElapsed < duration && duration > 0) {
		// linear elapsed duration
		float unitDuration = interpElapsed / duration;
		if (mode == SIN) {
			// sinusoidal ramp up and ramp down
			float sinPortion = (cos(-PI * unitDuration) / 2) + 0.5;
			unitDuration = sinPortion;
		}
		float setpointDiff = endSetpoint - startSetpoint;
		float newSetpoint = startSetpoint + (setpointDiff * unitDuration);
		Setpoint = newSetpoint;
	} else {
		// If there is no interpoation to perform, set the setpoint to the end state
		Setpoint = endSetpoint;
	}
	calcVel(); // ensure the velocity value is kept up to date
	if (mode != VEL) {
		Input = (float) getPosition();
		bool thisErrPositive = (Setpoint - Input) > 0;
		if (thisErrPositive != lastErrPositive) {
			myPID.clearIntegralBuffer();
		}
		lastErrPositive = thisErrPositive;
		Output = myPID.calc(Setpoint, Input);
		setOutputUnitVector(Output);
	} else {
		velocityLoop();
	}
}
void PIDMotor::velocityLoop() {
	double openLoopTerm = myFmap(targetDegreesPerSecond, -getFreeSpinMaxDegreesPerSecond(), getFreeSpinMaxDegreesPerSecond(),
				-1, 1);
	// TODO Apply PD velocity terms here
	setOutputUnitVector(openLoopTerm);
}

void PIDMotor::SetTuningsVelocity(double Kp, double Kd) {
	velocityPID.setpid(Kp, 0, Kd);

}
void PIDMotor::setVelocityDegreesPerSecond(float degreesPerSecond) {
	if (abs(degreesPerSecond) > 0) {
		if(degreesPerSecond>getFreeSpinMaxDegreesPerSecond())
			degreesPerSecond=getFreeSpinMaxDegreesPerSecond();
		if(degreesPerSecond<-getFreeSpinMaxDegreesPerSecond())
					degreesPerSecond=-getFreeSpinMaxDegreesPerSecond();
		targetDegreesPerSecond = degreesPerSecond;
		mode = VEL;
	} else {
		stop();
	}

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
	startInterpolation((float) val, 0, LIN);
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

double PIDMotor::getVelocityDegreesPerSecond() {
	return calcVel();
}
double PIDMotor::getAngleDegrees() {
	double curPos = getPosition();
	return curPos / ticksToDeg();
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
		return Vel;	// If this is polled too fast, return the cached velocity
	//encoder ticks since last call
	movement = curPos - prevPos;
	//encoder ticks to degrees
	movement = movement / ticksToDeg();
	//timeInterval in seconds
	timeInterval = timeInterval / 1000;
	//Velocity in degrees per seconds
	Vel = movement / timeInterval;
	//sets curent vals to previous
	prevPos = curPos;
	prevTime = curTime;
	return Vel;
}

void PIDMotor::stop() {
	setSetpoint(getPosition());
}

void PIDMotor::startInterpolation(float newSetpoint, long msTimeDuration,
		interpolateMode mode) {
	startSetpoint = Setpoint;
	endSetpoint = newSetpoint;
	startTime = millis();
	duration = msTimeDuration;
	this->mode = mode;
}
