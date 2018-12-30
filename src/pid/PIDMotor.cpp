/*
 * PIDMotor.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: hephaestus
 */

#include "PIDMotor.h"
#include <Arduino.h>
// Custom version of map with bound clamping built in.
float myFmap(float x, float in_min, float in_max, float out_min,
		float out_max) {
	if(x>in_max)
		return out_max;
	if(x<in_min)
		return out_min;
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
	// Done Performing linear/sinusoidal interpolation
	calcVel(); // ensure the velocity value is kept up to date
	if (mode != VEL) {
		// Position mode
		Input = (float) getPosition();
		//check for integral windup
		bool thisErrPositive = (Setpoint - Input) > 0;
		if (thisErrPositive != lastErrPositive) {
			myPID.clearIntegralBuffer();
		}
		lastErrPositive = thisErrPositive;
		// done with integral windup
		// run the PID compute function
		Output = myPID.calc(Setpoint, Input);
		// use the unit vector function to set the output of the PID
		setOutputUnitVector(Output);
	} else {
		velocityLoop();
	}
}
void PIDMotor::velocityLoop() {
	double openLoopTerm = myFmap(targetDegreesPerSecond,
			-getFreeSpinMaxDegreesPerSecond(), getFreeSpinMaxDegreesPerSecond(),
			-1, 1);
	// TODO Apply PD velocity terms here, 2002 velocity lab
	setOutputUnitVector(openLoopTerm);
}

void PIDMotor::SetTuningsVelocity(double Kp, double Kd) {
	velocityPID.setpid(Kp, 0, Kd);

}
void PIDMotor::setVelocityDegreesPerSecond(float degreesPerSecond) {
	if (abs(degreesPerSecond) > 0) {
		if (degreesPerSecond > getFreeSpinMaxDegreesPerSecond())
			degreesPerSecond = getFreeSpinMaxDegreesPerSecond();
		if (degreesPerSecond < -getFreeSpinMaxDegreesPerSecond())
			degreesPerSecond = -getFreeSpinMaxDegreesPerSecond();
		targetDegreesPerSecond = degreesPerSecond;
		mode = VEL;
	} else {
		stop();
	}

}
// Set the output using a -1.0f to 1.0f unit vector.
// Zero is stop
// This creates the dis-continuous signel needed to bypass deadbands in the actuator
// from a continous signel with range -1.0f to 1.0f.
void PIDMotor::setOutputUnitVector(float out) {
	// Store the unit vector output set
	Output = out;
	// default to stop
	hardwareOutput = getOutputStop();
	if (Output == 0.0) {
		// read the stop value from the subclass and set it to the hardware output
		hardwareOutput = getOutputStop();
	} else if (Output > 1.0) {
		// read the max value from the subclass and set it to the hardware output
		hardwareOutput = getOutputMax();
	} else if (Output < -1.0) {
		// read the min value from the subclass and set it to the hardware output
		hardwareOutput = getOutputMin();
	} else {
		if (Output > 0)
			// for positive signel, use the upper deadband to max
			hardwareOutput = myFmap(Output, 0, 1,
					getOutputStop() + getOutputMaxDeadbad(), getOutputMax());
		else
			// for negative signel, use the lower deadband to min
			hardwareOutput = myFmap(Output, -1, 0, getOutputMin(),
					getOutputStop() - getOutputMinDeadbad());
	}
	// with the hardwre value computed, send to sublcass output set
	setOutput(hardwareOutput);
}
// Set the current position to be the one provided
// this is for calibrations
void PIDMotor::overrideCurrentPosition(int64_t val) {
	overrideCurrentPositionHardware(val);

	setSetpoint(val);
	myPID.setpid(Kp, Ki, Kd);
	myPID.clearIntegralBuffer();
}
// Set the desired setpoint for the PID controller
// the units for the variable is in sensor 'ticks'
// this will start a linear interpolation of 0 time
void PIDMotor::setSetpoint(int64_t val) {
	startInterpolation((float) val, 0, LIN);
}

// Get the desired setpoint for the PID controller
// the units for the variable is in sensor 'ticks'
float PIDMotor::getSetPoint() {
	return Setpoint;
}

// Ser the P.I.D. gains for the position controller
void PIDMotor::SetTunings(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	overrideCurrentPosition(getPosition());
}
// Get the angular velocity of the shaft
// units are in degrees per second
double PIDMotor::getVelocityDegreesPerSecond() {
	return calcVel();
}
// Get the angular position of the shaft
// units are in degrees
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
// Set the PID position to current position and use the position controller to hold pose
void PIDMotor::stop() {
	setSetpoint(getPosition());
}
// Start a linear interpolation of the motor
// The position setpoint will follow a trajectory over time
// the setpoint will start where it currently is, and arrive at the desired location after
// the number of msTimeDuration MS have elapsed.
// The trajectory can be either linear, with the LIN mode
// or the trajectory can be either Sinusoidal, with the SIN mode
// the units for the variable is in sensor 'ticks'
void PIDMotor::startInterpolation(float newSetpoint, long msTimeDuration,
		interpolateMode mode) {
	startSetpoint = Setpoint;
	endSetpoint = newSetpoint;
	startTime = millis();
	duration = msTimeDuration;
	this->mode = mode;
}
