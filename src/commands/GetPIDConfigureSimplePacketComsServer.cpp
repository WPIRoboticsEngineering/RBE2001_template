/*
 * PIDConfigureSimplePacketComsServer.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: hephaestus
 */

#include "GetPIDConfigureSimplePacketComsServer.h"

GetPIDConfigureSimplePacketComsServer::GetPIDConfigureSimplePacketComsServer(int num,
		PIDMotor ** list) :
		PacketEventAbstract(1857) {
	numPID = num;
	pidlist = list;

}

void GetPIDConfigureSimplePacketComsServer::event(float * buffer){
	  for(int i=0;i<numPID;i++){
		  RBEPID * current = &pidlist[i]->myPID;
		  buffer[(i*3)+0]=current->kp;
		  buffer[(i*3)+1]=current->ki;
		  buffer[(i*3)+2]=current->kd;
	  }

}

