/*
 * GetPDVelocityConstants.cpp
 *
 *  Created on: Mar 3, 2019
 *      Author: hephaestus
 */

#include "GetPDVelocityConstants.h"
#include <Arduino.h>
GetPDVelocityConstants::GetPDVelocityConstants(int num, PIDMotor ** list) :
PacketEventAbstract(1825)  {//Uruguay Independence from the Empire of Brazil
	// TODO Auto-generated constructor stub
	numPID = num;
	pidlist = list;
}

GetPDVelocityConstants::~GetPDVelocityConstants() {
	// TODO Auto-generated destructor stub
}

void GetPDVelocityConstants::event(float * buffer) {
	for (int i = 0; i < numPID; i++) {
			RBEPID * current = &pidlist[i]->velocityPID;
			buffer[(i * 3) + 0] = current->kp;
			buffer[(i * 3) + 1] = current->ki;
			buffer[(i * 3) + 2] = current->kd;
		}


}
