#include "PickOrder.h"


//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void PickOrder::event(float * buffer) {
	int numberOfFloats = 15;
	float pickupMaterial = buffer[0];
	float dropoffAngle = buffer[1];
	float dropoffPosition = buffer[2];
	Serial.println(
			"Pick Order Recived from : " + String(pickupMaterial) + " "
					+ String(dropoffAngle) + " " + String(dropoffPosition) );
	robotPointer->myStatus=Waiting_for_approval_to_pickup;
}
