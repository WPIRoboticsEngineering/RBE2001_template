/*
 * GearWrist.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: hephaestus
 */

#include "GearWrist.h"

GearWrist::GearWrist(PIDMotor * left, PIDMotor * right,double ticksToADegrees, double wristRatio) {
	this->left = left;
	this->right = right;
	this->ticksToADegrees=ticksToADegrees;
	this->wristRatio=wristRatio;
}

GearWrist::~GearWrist() {
	// TODO Auto-generated destructor stub
}

void GearWrist::setTarget(double a, double b){
	double lmotor = a*ticksToADegrees+(b*wristRatio)*ticksToADegrees;
	double rmotor = a*ticksToADegrees-(b*wristRatio*ticksToADegrees);

	left->setSetpoint(lmotor);
	right->setSetpoint(-rmotor);
}
double GearWrist::getA(){
	double lticks = left->getPosition();
	double rticks = -right->getPosition();
	double diff = (lticks-rticks);
	double aTicks = lticks-diff/2;
	return aTicks/ticksToADegrees;
}
double GearWrist::getB(){
	double lticks = left->getPosition();
	double rticks = -right->getPosition();
	double diff = (lticks-rticks)/wristRatio/2;
	//double aTicks = lticks-diff;
	return diff/ticksToADegrees;
}

void GearWrist::loop(){
	left->loop();
	right->loop();
}
