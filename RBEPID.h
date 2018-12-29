/*
 * Messages.h
 *
 *  Created on: 10/1/16
 *      Author: joest
 */

#ifndef PID_H_
#define PID_H_

class RBEPID {

public:
	RBEPID();
	float kp=1;
	float ki=0;
	float kd=0;
	float last_error = 0;
	float sum_error = 0;
	int sampleRateMs =5;
//set PID constants
	void setpid(float P, float I, float D);
//calculate the output control signal
	float calc(double setVel, double curVel);
	//Clear the internal representation fo the integral term.
	void clearIntegralBuffer();
private:

};

#endif
