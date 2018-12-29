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
	virtual void setOutput(int64_t out)=0;
	double calcVel();
	float startSetpoint = 0;
	float endSetpoint = 0;
	float startTime = 0;
	float duration = 0;
	interpolateMode mode = LIN;
	float targetDegreesPerSecond = 0;
public:
	RBEPID myPID;
	RBEPID velocityPID;
	int64_t hardwareOutput = 0;
	PIDMotor();
	virtual ~PIDMotor();
	void loop();
	void velocityLoop();
	void overrideCurrentPosition(int64_t val);
	void setSetpoint(int64_t val);
	void SetTunings(double Kp, double Ki, double Kd);
	void SetTuningsVelocity(double Kp, double Kd);
	void setVelocityDegreesPerSecond(float degreesPerSecond);
	void pidinit();
	float getSetPoint();
	double getVelocityDegreesPerSecond();
	double getAngleDegrees();
	void setOutputUnitVector(float out);
	void stop();
	void startInterpolation(float newSetpoint, long msTimeDuration,
			interpolateMode mode);

	virtual int64_t getPosition()=0;
	virtual int64_t getOutputMin()=0;
	virtual int64_t getOutputMax()=0;
	virtual int64_t getOutputMinDeadbad()=0;
	virtual int64_t getOutputMaxDeadbad()=0;
	virtual int64_t getOutputStop()=0;
	virtual double ticksToDeg()=0;
	virtual void overrideCurrentPositionHardware(int64_t val)=0;
	virtual double calcCur(void)=0;
	virtual double getFreeSpinMaxDegreesPerSecond()=0;

};

#endif /* SRC_PIDMOTOR_H_ */
