#if !defined(CLEARFAULTS)
#define CLEARFAULTS
#include <SimplePacketComs.h>

#include "../../StudentsRobot.h"
class ClearFaults: public PacketEventAbstract {
	StudentsRobot * robotPointer;
public:
	// Packet ID needs to be set
	ClearFaults(StudentsRobot * robot) :
			PacketEventAbstract(1871) // Address of this event
	{
		robotPointer = robot;
	}
	virtual ~ClearFaults(){}
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
};
#endif
