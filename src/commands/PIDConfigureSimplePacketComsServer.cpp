/*
 * PIDConfigureSimplePacketComsServer.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: hephaestus
 */

#include "PIDConfigureSimplePacketComsServer.h"

PIDConfigureSimplePacketComsServer::PIDConfigureSimplePacketComsServer(int num,
		PIDMotor ** list) :
		PacketEventAbstract(1900) {
	numPID = num;
	pidlist = list;

}

void PIDConfigureSimplePacketComsServer::event(float * buffer){
	  for(int i=0;i<numPID;i++){
		  RBEPID * current = &pidlist[i]->myPID;
		  double kp=buffer[(i*3)+0];
		  double ki=buffer[(i*3)+1];
		  double kd=buffer[(i*3)+2];
		  current->setpid(kp,ki,kd);
	  }

}

