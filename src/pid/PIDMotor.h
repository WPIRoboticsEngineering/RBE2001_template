/*
 * PIDMotor.h
 *
 *  Created on: Oct 16, 2018
 *      Author: hephaestus
 */

#ifndef SRC_PIDMOTOR_H_
#define SRC_PIDMOTOR_H_
#include <stdint.h>
#include "../../RBEPID.h"
#include <math.h>
#define PID_OUTPUT_COMPUTE_RANGE 900

enum interpolateMode {
	LIN, SIN, VEL
};

class PIDMotor {
private:
	int32_t outputMin = -100;
	/**
	 * getOutputMax
	 *
	 * @return OutputMax
	 */
	int32_t outputMax = 100;
	/**
	 * getOutputMinDeadbad
	 *
	 * @return OutputMinDeadbad
	 */
	int32_t outputMinDeadbad = 0;
	/**
	 * getOutputMaxDeadbad
	 *
	 * @return OutputMaxDeadbad
	 */
	int32_t outputMaxDeadbad = 0;
	/**
	 * getOutputStop
	 *
	 * @return OutputStop
	 */
	int32_t outputStop = 0;
	/*
	 * a value to convert from degrees to motor units. This number times degrees equals ticks;
	 */
	double myTicksToDeg=1;
	/*
	 * value in degrees per second that represents the maximum
	 * freespinning speed of the motor running at 'outputMax'.
	 */
	double freeSpinMaxDegreesPerSecond=1000;
	/**
	 * The value that is being sent to the hardware
	 *
	 * View this variable in order to see what value is being sent to the motor directly
	 *
	 */
	int32_t hardwareOutput = 0;

protected:

	long lastTimeRunPID = 0;

	double Setpoint = 0, Input = 0, Output = 0;
	bool lastErrPositive = false;
	double curTime = 0;
	double prevTime = 0;
	double timeInterval = 0;
	double movement = 0;
	double prevPos = 0;
	double Vel = 0;

	/**
	 * virtual setOutput Set the motor in raw motor units
	 *
	 * this value should be pre scalled to match the motors range
	 * the zero deadbanding should already be taken care of
	 *
	 */
	virtual void setOutput(int32_t out)=0;
	/**
	 * Returns Vel in degress/second
	 *
	 * @return  Returns Vel in degress/second
	 */
	double calcVel();
	float startSetpoint = 0;
	float endSetpoint = 0;
	float startTime = 0;
	float duration = 0;
	interpolateMode mode = LIN;
	float targetDegreesPerSecond = 0;
	/**
	 * myFmap local mapping function
	 *
	 *  Custom version of map with bound clamping built in.
	 */
	float myFmap(float x, float in_min, float in_max, float out_min,
			float out_max);
	/**
	 * Get the setpoint
	 *
	 * @return the setpoint in sensor "Ticks"
	 */
	float getSetPoint();
public:
	/**
	 * The value that is being sent to the hardware
	 *
	 * View this variable in order to see what value is being sent to the motor directly
	 *
	 */
	int32_t getHardwareOutput();
	/**
	 * Duration of the interpolation mode, 1 equals done, 0 starting
	 */
	float unitDuration = 1;
	/**
	 * The PID object for the position controller
	 */
	RBEPID myPID;
	/**
	 * THe PID object for the velocity controller (UNIMPLEMENTED)
	 */
	RBEPID velocityPID;

	PIDMotor();
	virtual ~PIDMotor();
	/**
	 * Perform the PID calculations and apply the result to the actuators
	 */
	void loop();
	/**
	 * velocityLoop updates teh output in velocity mode
	 */
	void velocityLoop();
	/**
	 * overrideCurrentPosition  Set the current position to be the one provided
	 *
	 * this is for calibrations
	 */
	void overrideCurrentPosition(int32_t val);
	/**
	 * setSetpoint  Set the desired setpoint for the PID controller
	 *
	 * the units for the variable is in sensor 'ticks'
	 * this will start a linear interpolation of 0 time
	 */
	void setSetpoint(int32_t val);
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
	 * @param newSetpoint the new setpoint in motor ticks
	 * @param msTimeDuration the time of translation in miliseconds
	 * @param mode The type of interpolation LIN or SIN
	 * @note To get immediate action set msTimeDuration to 0
	 */
	void startInterpolation(float newSetpoint, long msTimeDuration,
			interpolateMode mode);
	/**
	 * isInterpolationDone check if the interpolation is done or not
	 * @return bool is the interpolation done
	 */
	bool isInterpolationDone();
	/**
	 * getInterpolationUnitIncrement A unit vector from
	 * 0 to 1 representing the state of the interpolation.
	 */
	float getInterpolationUnitIncrement();
	/**
	 * setSetpointDegrees  Set the desired setpoint for the PID controller
	 *
	 * the units for the variable is in Degrees
	 * this will start a linear interpolation of 0 time
	 */
	void setSetpointDegrees(float val);
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
	 * @param newSetpoint the new setpoint in degrees
	 * @param msTimeDuration the time of translation in miliseconds
	 * @param mode The type of interpolation LIN or SIN
	 * @note To get immediate action set msTimeDuration to 0
	 */
	void startInterpolationDegrees(float newSetpoint, long msTimeDuration,
			interpolateMode mode);

	/**
	 * SetTunings Set the P.I.D. gains for the position controller
	 *
	 * @param Kp proportional gain
	 * @param Ki integral gain
	 * @param Kd derrivitive gain
	 */
	void SetTunings(double Kp, double Ki, double Kd);
	/**
	 * SetTunings Set the P.I.D. gains for the velocity controller
	 *
	 * @param Kp proportional gain
	 * @param Kd derrivitive gain
	 *
	 * @note KI must be 0 for velocity
	 */
	void SetTuningsVelocity(double Kp, double Kd);
	/**
	 * Set the velocity of the motor
	 *
	 * This function defaults to open-loop estimation of velocity
	 * @param degreesPerSecond the motor speed in degrees Per Second
	 */
	void setVelocityDegreesPerSecond(float degreesPerSecond);
	/**
	 * Reset and clear the PID controller
	 */
	void pidinit();

	/**
	 * Get the setpoint
	 *
	 * @return the setpoint in degrees
	 */
	float getSetPointDegrees();
	/**
	 * Get the velocity of the plant
	 *
	 * @return the velocity in DegreesPerSecond
	 */
	double getVelocityDegreesPerSecond();
	/**
	 * Get the current position of the motor converted to Degrees
	 *
	 * @return teh position in degrees
	 */
	double getAngleDegrees();
	/**
	 * setOutputUnitVector Set the output using a -1.0f to 1.0f unit vector.
	 *
	 *  Zero is stop
	 *  This creates the dis-continuous signel needed to bypass deadbands in the actuator
	 *  from a continous signel with range -1.0f to 1.0f.
	 *  @param out the unit vector of the the motors output
	 */
	void setOutputUnitVector(float out);
	/**
	 * Stop the motion of the motor
	 *
	 * Set the PID position to current position and use the position controller to hold pose
	 */
	void stop();
	/**
	 * getOutputMin
	 *
	 * @return OutputMin
	 */
	int32_t getOutputMin();
	/**
	 * getOutputMax
	 *
	 * @return OutputMax
	 */
	int32_t getOutputMax();
	/**
	 * getOutputMinDeadbad
	 *
	 * @return OutputMinDeadbad
	 */
	int32_t getOutputMinDeadbad();
	/**
	 * getOutputMaxDeadbad
	 *
	 * @return OutputMaxDeadbad
	 */
	int32_t getOutputMaxDeadbad();
	/**
	 * getOutputStop
	 *
	 * @return OutputStop
	 */
	int32_t getOutputStop();
	/**
	 * getFreeSpinMaxDegreesPerSecond
	 *
	 * @return FreeSpinMaxDegreesPerSecond
	 */
	double getFreeSpinMaxDegreesPerSecond() ;
	/**
	 * ticksToDeg
	 *
	 * @return ticksToDeg
	 */
	double ticksToDeg();
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
	 */
	void setOutputBoundingValues(int32_t outputMin, int32_t outputMax,
			int32_t outputStop, int32_t outputMinDeadbad,
			int32_t outputMaxDeadbad, double ticksToDeg,
			double getFreeSpinMaxDegreesPerSecond);
	/**
	 * calcCur
	 *
	 * @return calcCur
	 */
	virtual double calcCur(void)=0;
	/**
	 * getPosition
	 *
	 * @return Position
	 */
	virtual int64_t getPosition()=0;

	/**
	 * overrideCurrentPositionHardware
	 *
	 * forces the hardware provider to return this value
	 * instead of its internal value and this position
	 *
	 * @param val the value to set the sensor to
	 */
	virtual void overrideCurrentPositionHardware(int64_t val)=0;

};

#endif /* SRC_PIDMOTOR_H_ */
