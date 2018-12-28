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
void StudentsRobot::updateStateMachine(PIDMotor * motor1,
		PIDMotor * motor2, PIDMotor * motor3,
		Servo * servo){
	switch(status){
	case StartupRobot:
		//Do this once at startup
		status=Running;
		break;
	case Running:
		// Do something
		break;
	case Halting:
		// save state and enter safe mode
		status=Halt;
		break;
	case Halt:
		// in safe mode
		break;

	}
}

void StudentsRobot::attach(HBridgeEncoderPIDMotor * motor1,
		HBridgeEncoderPIDMotor * motor2, ServoEncoderPIDMotor * motor3,
		Servo * servo) {
	motor1->attach(MOTOR1_PWM, MOTOR1_DIR, MOTOR1_ENCA, MOTOR1_ENCB);
	motor2->attach(MOTOR2_PWM, MOTOR2_DIR, MOTOR2_ENCA, MOTOR2_ENCB);
	motor3->attach(MOTOR3_PWM, MOTOR3_ENCA, MOTOR3_ENCB);

	Serial.println("Starting Motors");
	// Set up digital servos
	servo->setPeriodHertz(330);
	servo->attach(SERVO_PIN, 1000, 2000);
}

void StudentsRobot::pidLoop(PIDMotor * motor1,PIDMotor * motor2, PIDMotor * motor3){
	motor1->loop();
	motor2->loop();
	motor3->loop();
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
	status=Running;
}
void StudentsRobot::EStop(float * buffer) {
	// Stop the robot immediatly
	Serial.println("EStop::event");
	myCommandsStatus = Fault_E_Stop_pressed;
	status=Halting;

}
void StudentsRobot::PickOrder(float * buffer) {
	float pickupMaterial = buffer[0];
	float dropoffAngle = buffer[1];
	float dropoffPosition = buffer[2];
	Serial.println(
			"Pick Order Recived from : " + String(pickupMaterial) + " "
					+ String(dropoffAngle) + " " + String(dropoffPosition));
	myCommandsStatus = Waiting_for_approval_to_pickup;
}
