/*
 * SetPIDVelocity.cpp
 *
 *  Created on: Mar 3, 2019
 *      Author: hephaestus
 */

#include "SetPIDVelocity.h"
#include <Arduino.h>
SetPIDVelocity::SetPIDVelocity(int num, PIDMotor ** list) :
PacketEventAbstract(1811)  {//Venezuela's independence
	// TODO Auto-generated constructor stub
	numPID = num;
	pidlist = list;
}

SetPIDVelocity::~SetPIDVelocity() {
	// TODO Auto-generated destructor stub
}

void SetPIDVelocity::event(float * buffer) {

	for (int i = 0; i < numPID; i++) {
		float val = buffer[i];
		if(val==0)
			continue;
		Serial.println("Set Velocity "+String(i)+" to "+String(val));
		pidlist[i]->setVelocityDegreesPerSecond(val);
	}

}
