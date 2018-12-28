/*
 * GearWrist.h
 *
 *  Created on: Oct 16, 2018
 *      Author: hephaestus
 */

#ifndef SRC_GEARWRIST_H_
#define SRC_GEARWRIST_H_
#include "PIDMotor.h"
class GearWrist {
private:
	PIDMotor * left;
	PIDMotor * right;
	double ticksToADegrees, wristRatio;
public:
	GearWrist(PIDMotor * left, PIDMotor * right,double ticksToADegrees, double wristRatio);
	virtual ~GearWrist();
	void setTarget(double a, double b);
	double getA();
	double getB();
	void loop();
};

#endif /* SRC_GEARWRIST_H_ */
