/*
 * SetPIDSetpoint.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: hephaestus
 */

#include "SetPIDSetpoint.h"

SetPIDSetpoint::SetPIDSetpoint(int num, PIDMotor ** list) :
		PacketEventAbstract(1848) {
	numPID = num;
	pidlist = list;

}

void SetPIDSetpoint::event(float * buffer) {
	float duration = buffer[0];
	interpolateMode type = buffer[1]<1?LIN:SIN;
	for (int i = 0; i < numPID; i++) {
		pidlist[i]->startInterpolationDegrees(buffer[i+2], duration, type);
	}

}
