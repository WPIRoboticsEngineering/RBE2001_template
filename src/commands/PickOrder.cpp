#include "PickOrder.h"


//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void PickOrder::event(float * buffer) {
	int numberOfFloats = 15;
	float pickupArea = buffer[0];
	float pickupX = buffer[1];
	float pickupZ = buffer[2];
	float dropOffArea = buffer[3];
	float dropOffX = buffer[4];
	float dropOffZ = buffer[5];
	Serial.println(
			"Pick Order Recived from : " + String(pickupArea) + " "
					+ String(pickupX) + " " + String(pickupZ) + " to : "
					+ String(dropOffArea) + " " + String(dropOffX) + " "
					+ String(dropOffZ));
}
