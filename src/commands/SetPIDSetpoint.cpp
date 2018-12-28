/*
 * SetPIDSetpoint.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: hephaestus
 */

#include "SetPIDSetpoint.h"


SetPIDSetpoint::SetPIDSetpoint(int num,
		PIDMotor ** list) :
		PacketEventAbstract(1848) {
	numPID = num;
	pidlist = list;

}

void SetPIDSetpoint::event(float * buffer){
	for(int i=0;i<numPID;i++){
		pidlist[i]->setSetpoint(buffer[i]);
	}

}
