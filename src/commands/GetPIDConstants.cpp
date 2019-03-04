/*
 * PIDConfigureSimplePacketComsServer.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: hephaestus
 */

#include "GetPIDConstants.h"
#include <Arduino.h>

GetPIDConstants::GetPIDConstants(int num, PIDMotor ** list) :
		PacketEventAbstract(1857) {
	numPID = num;
	pidlist = list;

}

void GetPIDConstants::event(float * buffer) {
	for (int i = 0; i < numPID; i++) {
		RBEPID * current = &pidlist[i]->myPID;
		buffer[(i * 3) + 0] = current->kp;
		buffer[(i * 3) + 1] = current->ki;
		buffer[(i * 3) + 2] = current->kd;
		Serial.print("\r\nGetting gains index "+String(i));
		Serial.print(" p= ");Serial.print(current->kp,6);
		Serial.print(" i= ");Serial.print(current->ki,6);
		Serial.print(" d= ");Serial.print(current->kd,6);
	}

}

