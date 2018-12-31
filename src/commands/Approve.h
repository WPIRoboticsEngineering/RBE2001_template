#if !defined(APPROVE_H)
#define APPROVE_H
#include <SimplePacketComs.h>

#include "../../StudentsRobot.h"
class Approve: public PacketEventAbstract {
	StudentsRobot * robotPointer;
public:
	// Packet ID needs to be set
	Approve(StudentsRobot * robot) :
			PacketEventAbstract(1994) // Address of this event
	{
		robotPointer = robot;
	}
	~Approve(){}
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
};
#endif
