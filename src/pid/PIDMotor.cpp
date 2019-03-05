/*
 * PIDMotor.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: hephaestus
 */

#include "PIDMotor.h"
#include <Arduino.h>

/**
 * myFmap local mapping function
 *
 *  Custom version of map with bound clamping built in.
 */
float PIDMotor::myFmap(float x, float in_min, float in_max, float out_min,
		float out_max) {
	if (x > in_max)
		return out_max;
	if (x < in_min)
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
/**
 * getInterpolationUnitIncrement A unit vector from
 * 0 to 1 representing the state of the interpolation.
 */
float PIDMotor::getInterpolationUnitIncrement(){
	float interpElapsed = (float) (millis() - startTime);
	if(interpElapsed < duration && duration > 0){
		// linear elapsed duration
		unitDuration = interpElapsed / duration;
		if (mode == SIN) {
			// sinusoidal ramp up and ramp down
			float sinPortion = (cos(-PI * unitDuration) / 2) + 0.5;
			unitDuration = 1 - sinPortion;
		}
		return unitDuration;
	}
	return 1;
}
/**
 * isInterpolationDone check if the interpolation is done or not
 * @return bool is the interpolation done
 */
bool PIDMotor::isInterpolationDone() {
	if (getInterpolationUnitIncrement()<1)
		return false;
	return true;
}

void PIDMotor::loop() {
	calcVel(); // ensure the velocity value is kept up to date
	if (millis() - lastTimeRunPID > myPID.sampleRateMs) {
		lastTimeRunPID = millis();
	} else {
		return;
	}
	// Done Performing linear/sinusoidal interpolation
	if (mode != VEL) {
		// Perform linear/sinusoidal interpolation
		unitDuration=getInterpolationUnitIncrement();
		if (unitDuration<1) {
			float setpointDiff = endSetpoint - startSetpoint;
			float newSetpoint = startSetpoint + (setpointDiff * unitDuration);
			Setpoint = newSetpoint;
		} else {
			// If there is no interpoation to perform, set the setpoint to the end state
			Setpoint = endSetpoint;
		}
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
	double openLoopTerm=0;
	if(targetDegreesPerSecond>0)
		openLoopTerm= myFmap(targetDegreesPerSecond,
				freeSpinMinDegreesPerSecond, getFreeSpinMaxDegreesPerSecond(),
			0, 1);
	else
		openLoopTerm= myFmap(targetDegreesPerSecond,
						-getFreeSpinMaxDegreesPerSecond(),
						-freeSpinMinDegreesPerSecond,
					-1,0);
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
		if(degreesPerSecond>0 && degreesPerSecond < freeSpinMinDegreesPerSecond)
			degreesPerSecond=freeSpinMinDegreesPerSecond;
		if(degreesPerSecond<0 && degreesPerSecond > -freeSpinMinDegreesPerSecond)
			degreesPerSecond=-freeSpinMinDegreesPerSecond;
		targetDegreesPerSecond = degreesPerSecond;
		mode = VEL;
	} else {
		stop();
	}

}

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
/**
 * overrideCurrentPosition  Set the current position to be the one provided
 *
 * this is for calibrations
 */
void PIDMotor::overrideCurrentPosition(int32_t val) {
	overrideCurrentPositionHardware(val);

	startInterpolation((float) val, 0, LIN);

	myPID.clearIntegralBuffer();
}
/**
 * setSetpoint  Set the desired setpoint for the PID controller
 *
 * the units for the variable is in sensor 'ticks'
 * this will start a linear interpolation of 0 time
 */
void PIDMotor::setSetpoint(int32_t val) {
	startInterpolation((float) val, 0, LIN);
}

// Get the desired setpoint for the PID controller
// the units for the variable is in sensor 'ticks'
float PIDMotor::getSetPoint() {
	return Setpoint;
}

float PIDMotor::getSetPointDegrees() {
	return getSetPoint() / ticksToDeg();
}
/**
 * SetTunings Set the P.I.D. gains for the position controller
 *
 * @param Kp proportional gain
 * @param Ki integral gain
 * @param Kd derrivitive gain
 */
void PIDMotor::SetTunings(double Kp, double Ki, double Kd) {
	myPID.setpid(Kp, Ki, Kd);
	overrideCurrentPosition(getPosition());
}
//
// Get the angular velocity of the shaft
// units are in degrees per second
//
double PIDMotor::getVelocityDegreesPerSecond() {
	return calcVel();
}
// Get the angular position of the shaft
// units are in degrees
double PIDMotor::getAngleDegrees() {
	double curPos = getPosition();
	return curPos / ticksToDeg();
}

/**
 * Returns Vel in degress/second
 *
 * @return  Returns Vel in degress/second
 */
double PIDMotor::calcVel() {
	//current positions
	double curPos = getPosition();
	//current time
	curTime = millis();
	//time change in ms from last call
	timeInterval = curTime - prevTime;
	if (timeInterval < 50)
		return Vel;	// If this is polled too fast, return the cached velocity
	//encoder ticks since last call
	movement = curPos - prevPos;
	//encoder ticks to degrees
	double movementdeg = movement / ticksToDeg();
	//timeInterval in seconds
	double timeIntervalsec = timeInterval / 1000.0;
	//Velocity in degrees per seconds
	Vel = movementdeg / timeIntervalsec;
	//Serial.println("Vel "+String(movementdeg)+" Per "+String(timeIntervalsec)+" is "+String(Vel)+" max "+String(getFreeSpinMaxDegreesPerSecond()));
	//sets curent vals to previous
	prevPos = curPos;
	prevTime = curTime;
	return Vel;
}
/**
 * Stop the motion of the motor
 *
 * Set the PID position to current position and use the position controller to hold pose
 */
void PIDMotor::stop() {
	setSetpoint(getPosition());
}
/**
 * Start a linear interpolation of the motor
 *
 * The position setpoint will follow a trajectory over time
 * the setpoint will start where it currently is, and arrive at the desired location after
 * the number of msTimeDuration MS have elapsed.
 * The trajectory can be either linear, with the LIN mode
 * or the trajectory can be either Sinusoidal, with the SIN mode
 * the units for the variable is in sensor 'ticks'
 *
 * @param newSetpoint the new setpoint
 * @param msTimeDuration the time of translation
 * @param mode The type of interpolation LIN or SIN
 */
void PIDMotor::startInterpolation(float newSetpoint, long msTimeDuration,
		interpolateMode mode) {
	if(newSetpoint==Setpoint &&msTimeDuration== duration&& this->mode==mode)
		return;
	startSetpoint = Setpoint;
	endSetpoint = newSetpoint;
	startTime = millis();
	duration = msTimeDuration;
	this->mode = mode;
	if(msTimeDuration<1){
		Setpoint=newSetpoint;
	}
}

/**
 * setSetpointDegrees  Set the desired setpoint for the PID controller
 *
 * the units for the variable is in Degrees
 * this will start a linear interpolation of 0 time
 */
void PIDMotor::setSetpointDegrees(float val) {
	setSetpoint((int32_t) (val * ticksToDeg()));
}
/**
 * Start a linear interpolation of the motor
 *
 * The position setpoint will follow a trajectory over time
 * the setpoint will start where it currently is, and arrive at the desired location after
 * the number of msTimeDuration MS have elapsed.
 * The trajectory can be either linear, with the LIN mode
 * or the trajectory can be either Sinusoidal, with the SIN mode
 * the units for the variable is in Degrees
 *
 * @param newSetpoint the new setpoint in Degrees
 * @param msTimeDuration the time of translation
 * @param mode The type of interpolation LIN or SIN
 */
void PIDMotor::startInterpolationDegrees(float newSetpoint, long msTimeDuration,
		interpolateMode mode) {
	startInterpolation(newSetpoint * ticksToDeg(), msTimeDuration, mode);
}

/**
 * Set the bounds of the output stage
 *
 * These are the values to determing the opperating range of the
 * output of this PID motor.
 * @param outputMin the minimum value that the output takes (Full reverse)
 * @param outputMax the maximum value the output takes (Full forwared)
 * @param outputStop the value of the output to stop moving
 * @param outputMinDeadbad a positive value added to the stop value to creep backward
 * @param outputMaxDeadbad a positive value subtracted from stop value to creep forwards
 * @param ticksToDeg a value to convert from degrees to motor units. This number times degrees equals ticks;
 * @param freeSpinMaxDegreesPerSecond a value in degrees per second that represents the maximum
 * 		freespinning speed of the motor running at 'outputMax'.
 * 	@param speedAtPositiveCreepValue the speed in degrees per second that the motor spins when the hardware output is at creep forwards
 */
void PIDMotor::setOutputBoundingValues(int32_t outputMin, int32_t outputMax,
		int32_t outputStop, int32_t outputMinDeadbad,
		int32_t outputMaxDeadbad, double ticksToDeg,
		double getFreeSpinMaxDegreesPerSecond,
		double speedAtPositiveCreepValue) {
	this->outputMin = outputMin;
	this->outputMax = outputMax;
	this->outputStop = outputStop;
	this->outputMinDeadbad = outputMinDeadbad;
	this->outputMaxDeadbad = outputMaxDeadbad;
	this->myTicksToDeg = ticksToDeg;
	this->freeSpinMaxDegreesPerSecond = getFreeSpinMaxDegreesPerSecond;
	freeSpinMinDegreesPerSecond=speedAtPositiveCreepValue;
}
/**
 * getOutputMin
 *
 * @return OutputMin
 */
int32_t PIDMotor::getOutputMin() {
	return outputMin;
}
;
/**
 * getOutputMax
 *
 * @return OutputMax
 */
int32_t PIDMotor::getOutputMax() {
	return outputMax;
}
;
/**
 * getOutputMinDeadbad
 *
 * @return OutputMinDeadbad
 */
int32_t PIDMotor::getOutputMinDeadbad() {
	return outputMinDeadbad;
}
;
/**
 * getOutputMaxDeadbad
 *
 * @return OutputMaxDeadbad
 */
int32_t PIDMotor::getOutputMaxDeadbad() {
	return outputMaxDeadbad;
}
;
/**
 * getOutputStop
 *
 * @return OutputStop
 */
int32_t PIDMotor::getOutputStop() {
	return outputStop;
}
/**
 * getFreeSpinMaxDegreesPerSecond
 *
 * @return FreeSpinMaxDegreesPerSecond
 */
double PIDMotor::getFreeSpinMaxDegreesPerSecond() {
	return freeSpinMaxDegreesPerSecond;
}
/**
 * ticksToDeg
 *
 * @return ticksToDeg
 */
double PIDMotor::ticksToDeg() {
	return myTicksToDeg;
}
/**
 * The value that is being sent to the hardware
 *
 * View this variable in order to see what value is being sent to the motor directly
 *
 */
int32_t  PIDMotor::getHardwareOutput(){
	return hardwareOutput;
}
