#include "GetLocation.h"
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void GetLocation::event(float * buffer) {
		int numberOfFloats = 15;
		buffer[0] = 10;	// X Location
		buffer[1] = 0;	// Y Location
		buffer[2] = 0;	// Z Location
		buffer[3] = 45;	// azimuth
		buffer[4] = 0;	// elevation
		buffer[5] = 0;	// tilt
		buffer[6] = 100;	// X size
		buffer[7] = 100;	// Y size
		buffer[8] = 100;	// Z size
//		Serial.println(
//				"Location request " + String(buffer[0]) + " "
//						+ String(buffer[1]) + " " + String(buffer[2]) + " "
//						+ String(buffer[3]) + " " + String(buffer[4]) + " "
//						+ String(buffer[5]) + " " + String(buffer[6]) + " "
//						+ String(buffer[7]) + " " + String(buffer[8]));
	}
