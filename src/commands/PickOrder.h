#include "../ExampleRobot.h"
#include <SimplePacketComs.h>
#include "Arduino.h"
#if !defined(PICKORDER)
#define PICKORDER
class PickOrder: public PacketEventAbstract {
	ExampleRobot* robotPointer;
public:
	// Packet ID needs to be set
	PickOrder(ExampleRobot* robot) :
			PacketEventAbstract(1936)	// Address of this event
	{
		robotPointer = robot;
	}
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
};
#endif
