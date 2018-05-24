/*
 * DirectDrive.h
 *
 *  Created on: May 24, 2018
 *      Author: hephaestus
 */

#ifndef LIBRARIES_RBE2001_SRC_COMMANDS_DIRECTDRIVE_H_
#define LIBRARIES_RBE2001_SRC_COMMANDS_DIRECTDRIVE_H_

#include <robot/MyRobot.h>
#include <SimplePacketComs.h>
#include "Arduino.h"


class DirectDrive: public PacketEventAbstract {
	MyRobot* robotPointer;
	float sessionIDPRevious=0;
public:
	// Packet ID needs to be set
	DirectDrive(MyRobot* robot) :
			PacketEventAbstract(1786)	// Address of this event
	{
		robotPointer = robot;
	}
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
};

#endif /* LIBRARIES_RBE2001_SRC_COMMANDS_DIRECTDRIVE_H_ */
