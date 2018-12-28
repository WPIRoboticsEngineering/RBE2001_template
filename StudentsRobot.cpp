/*
 * StudentsRobot.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: hephaestus
 */

#include "StudentsRobot.h"

StudentsRobot::StudentsRobot() {
	// TODO Auto-generated constructor stub

}

void StudentsRobot::Approve(float * data) {
	// approve the procession to new state
	Serial.println("Approve::event");

	if (myCommandsStatus == Waiting_for_approval_to_pickup) {
		myCommandsStatus = Waiting_for_approval_to_dropoff;
	} else {
		myCommandsStatus = Ready_for_new_task;
	}
}
void StudentsRobot::ClearFaults(float * data) {
	// clear the faults somehow
	Serial.println("ClearFaults::event");
	myCommandsStatus = Ready_for_new_task;
}
void StudentsRobot::EStop(float * buffer) {
	// Stop the robot immediatly
	Serial.println("EStop::event");
	myCommandsStatus = Fault_E_Stop_pressed;

}
void StudentsRobot::PickOrder(float * buffer) {
	int numberOfFloats = 15;
	float pickupMaterial = buffer[0];
	float dropoffAngle = buffer[1];
	float dropoffPosition = buffer[2];
	Serial.println(
			"Pick Order Recived from : " + String(pickupMaterial) + " "
					+ String(dropoffAngle) + " " + String(dropoffPosition));
	myCommandsStatus = Waiting_for_approval_to_pickup;
}
