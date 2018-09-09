#include "Approve.h"

//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void Approve::event(float * buffer) {
	// approve the procession to new state
	Serial.println("Approve::event");
	if(robotPointer->myStatus==Waiting_for_approval_to_pickup){
		robotPointer->myStatus=Waiting_for_approval_to_dropoff;
	}else{
		robotPointer->myStatus=Ready_for_new_task;
	}
}
