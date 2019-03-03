/*
 * GetPIDVelocity.cpp
 *
 *  Created on: Mar 3, 2019
 *      Author: hephaestus
 */

#include "GetPIDVelocity.h"
#include <Arduino.h>
GetPIDVelocity::GetPIDVelocity(int num, PIDMotor ** list) :
PacketEventAbstract(1822) {//Brazil's independence from Portugal,
	// TODO Auto-generated constructor stub
	numPID = num;
	pidlist = list;
}

GetPIDVelocity::~GetPIDVelocity() {
	// TODO Auto-generated destructor stub
}

void GetPIDVelocity::event(float * buffer) {
	buffer[0] = (float) numPID;
	for (int i = 0; i < numPID && i < 7; i++) {
		PIDMotor * current = pidlist[i];
		buffer[i * 3 + 1 + 0] = current->mode==VEL?current->targetDegreesPerSecond:0;
		buffer[i * 3 + 1 + 1] = current->getVelocityDegreesPerSecond();
		buffer[i * 3 + 1 + 2] = current->hardwareOutput;
	}

}
