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
protected:

	long lastTimeRunPID = 0;
	float Kp = 5, Ki = 1.5, Kd = 0.1;
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
	virtual void setOutput(int64_t out)=0;
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
	float myFmap(float x, float in_min, float in_max, float out_min,float out_max);
public:
	/**
	 * The PID object for the position controller
	 */
	RBEPID myPID;
	/**
	 * THe PID object for the velocity controller (UNIMPLEMENTED)
	 */
	RBEPID velocityPID;
	/**
	 * The value that is being sent to the hardware
	 *
	 * View this variable in order to see what value is being sent to the motor directly
	 *
	 */
	int64_t hardwareOutput = 0;
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
	void overrideCurrentPosition(int64_t val);
	/**
	 * setSetpoint  Set the desired setpoint for the PID controller
	 *
	 * the units for the variable is in sensor 'ticks'
	 * this will start a linear interpolation of 0 time
	 */
	void setSetpoint(int64_t val);
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
	 * @return the setpoint in sensor "Ticks"
	 */
	float getSetPoint();
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
	void startInterpolation(float newSetpoint, long msTimeDuration,interpolateMode mode);
	/**
	 * getPosition
	 *
	 * @return Position
	 */
	virtual int64_t getPosition()=0;
	/**
		 * getOutputMin
		 *
		 * @return OutputMin
		 */
	virtual int64_t getOutputMin()=0;
	/**
		 * getOutputMax
		 *
		 * @return OutputMax
		 */
	virtual int64_t getOutputMax()=0;
	/**
		 * getOutputMinDeadbad
		 *
		 * @return OutputMinDeadbad
		 */
	virtual int64_t getOutputMinDeadbad()=0;
	/**
		 * getOutputMaxDeadbad
		 *
		 * @return OutputMaxDeadbad
		 */
	virtual int64_t getOutputMaxDeadbad()=0;
	/**
		 * getOutputStop
		 *
		 * @return OutputStop
		 */
	virtual int64_t getOutputStop()=0;
	/**
		 * ticksToDeg
		 *
		 * @return ticksToDeg
		 */
	virtual double ticksToDeg()=0;
	/**
			 * overrideCurrentPositionHardware
			 *
			 * forces the hardware provider to return this value
			 * instead of its internal value and this position
			 *
			 * @param val the value to set the sensor to
			 */
	virtual void overrideCurrentPositionHardware(int64_t val)=0;
	/**
		 * calcCur
		 *
		 * @return calcCur
		 */
	virtual double calcCur(void)=0;
	/**
		 * getFreeSpinMaxDegreesPerSecond
		 *
		 * @return FreeSpinMaxDegreesPerSecond
		 */
	virtual double getFreeSpinMaxDegreesPerSecond()=0;

};

#endif /* SRC_PIDMOTOR_H_ */
