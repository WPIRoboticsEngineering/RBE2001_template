/*
 * GetStatus.h
 *
 *  Created on: May 24, 2018
 *      Author: hephaestus
 */

#ifndef LIBRARIES_RBE2001_SRC_COMMANDS_GETSTATUS_H_
#define LIBRARIES_RBE2001_SRC_COMMANDS_GETSTATUS_H_

#include <SimplePacketComs.h>
#include "../AbstractRobot.h"


class GetStatus: public PacketEventAbstract {
	AbstractRobot* robotPointer;

public:
	// Packet ID needs to be set
	GetStatus(AbstractRobot* robot) :
			PacketEventAbstract(2012)	// Address of this event
	{
		robotPointer = robot;
	}
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
};

#endif /* LIBRARIES_RBE2001_SRC_COMMANDS_GETSTATUS_H_ */
