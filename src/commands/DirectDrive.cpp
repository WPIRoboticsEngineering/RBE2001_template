/*
 * DirectDrive.cpp
 *
 *  Created on: May 24, 2018
 *      Author: hephaestus
 */

//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
#include "DirectDrive.h"

void DirectDrive::event(float * buffer) {
	int numberOfFloats = 15;
	float deltax = buffer[0];
	float deltaY = buffer[1];
	float deltaZ = buffer[2];
	float deltaAzimuth = buffer[3];
	float deltaElevation = buffer[4];
	float deltaTilt = buffer[5];
	float milisecondsFOrTrasnition = buffer[6];
	float sessionID = buffer[7];
	float status = 0;
	if (sessionIDPRevious != sessionID) {
		sessionIDPRevious = sessionID;
		Serial.println(
				"Direct Drive Recived : " + String(deltax) + " "
						+ String(deltaY) + " " + String(deltaZ) + "  "
						+ String(deltaAzimuth) + " " + String(deltaElevation)
						+ " " + String(deltaTilt)) + " "
				+ String(milisecondsFOrTrasnition) + " " + String(sessionID)
				+ " " + String(status);
	}
	buffer[0] = status;
}
