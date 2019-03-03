/*
 * SetPDVelocityConstants.cpp
 *
 *  Created on: Mar 3, 2019
 *      Author: hephaestus
 */

#include "SetPDVelocityConstants.h"
#include <Arduino.h>
SetPDVelocityConstants::SetPDVelocityConstants(int num, PIDMotor ** list) :
PacketEventAbstract(1810)  {//The Colombian Declaration of Independence
	// TODO Auto-generated constructor stub
	numPID = num;
	pidlist = list;
}

SetPDVelocityConstants::~SetPDVelocityConstants() {
	// TODO Auto-generated destructor stub
}

void SetPDVelocityConstants::event(float * buffer) {
	for (int i = 0; i < numPID; i++) {
		double kp = buffer[(i * 3) + 0];
		double ki = buffer[(i * 3) + 1];
		double kd = buffer[(i * 3) + 2];
		Serial.print("\r\nSetting gains index "+String(i));
		Serial.print(" p= ");Serial.print(kp,6);
		Serial.print(" i= ");Serial.print(ki,6);
		Serial.print(" d= ");Serial.print(kd,6);

		pidlist[i]->velocityPID.setpid(kp, ki, kd);
	}

}
