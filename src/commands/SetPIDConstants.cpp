/*
 * PIDConfigureSimplePacketComsServer.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: hephaestus
 */

#include "SetPIDConstants.h"

SetPIDConstants::SetPIDConstants(int num,
		PIDMotor ** list) :
		PacketEventAbstract(1900) {
	numPID = num;
	pidlist = list;

}

void SetPIDConstants::event(float * buffer){
	  for(int i=0;i<numPID;i++){
		  double kp=buffer[(i*3)+0];
		  double ki=buffer[(i*3)+1];
		  double kd=buffer[(i*3)+2];
		  pidlist[i]->SetTunings(kp,ki,kd);
	  }

}

