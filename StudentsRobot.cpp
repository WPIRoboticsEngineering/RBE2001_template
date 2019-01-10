/*
 * StudentsRobot.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: hephaestus
 */

#include "StudentsRobot.h"

StudentsRobot::StudentsRobot(ServoEncoderPIDMotor * motor1,
		ServoEncoderPIDMotor * motor2, HBridgeEncoderPIDMotor * motor3,
		Servo * servo) {
	Serial.println("StudentsRobot::StudentsRobot called here ");
	this->servo = servo;
	this->motor1 = motor1;
	this->motor2 = motor2;
	this->motor3 = motor3;
	motor1->attach(MOTOR1_PWM, MOTOR1_ENCA, MOTOR1_ENCB);
	motor2->attach(MOTOR2_PWM, MOTOR2_ENCA, MOTOR2_ENCB);
	motor3->attach(MOTOR3_PWM, MOTOR3_DIR, MOTOR3_ENCA, MOTOR2_ENCB);
	// Set the PID CLock gating rate
	motor1->myPID.sampleRateMs=30;
	motor2->myPID.sampleRateMs=30;
	motor3->myPID.sampleRateMs=1;

	// After attach, compute ratios
	/**
	 * Set the bounds of the output stage
	 *
	 * These are the values to determing the opperating range of the
	 * output of this PID motor.
	 */
	double motorToWheel = 3;
	motor1->setOutputBoundingValues(0, //the minimum value that the output takes (Full reverse)
			180, //the maximum value the output takes (Full forward)
			90, //the value of the output to stop moving
			5, //a positive value added to the stop value to creep backward
			5, //a positive value subtracted from stop value to creep forwards
			16.0 * // Encoder CPR
					50.0 * // Motor Gear box ratio
					motorToWheel * // motor to wheel stage ratio
					(1.0 / 360.0) * // degrees per revolution
					motor1->encoder.countsMode,// Number of edges that are used to increment the value
					117.5 * // Measured max RPM
					(1/60.0) * // Convert to seconds
					(1/motorToWheel)*  // motor to wheel ratio
					360.0); // convert to degrees
	motor2->setOutputBoundingValues(0, //the minimum value that the output takes (Full reverse)
			180, //the maximum value the output takes (Full forward)
			90, //the value of the output to stop moving
			5, //a positive value added to the stop value to creep backward
			5, //a positive value subtracted from stop value to creep forwards
			16.0 * // Encoder CPR
					50.0 * // Motor Gear box ratio
					motorToWheel * // motor to wheel stage ratio
					(1.0 / 360.0) * // degrees per revolution
					motor1->encoder.countsMode,// Number of edges that are used to increment the value
					117.5 * // Measured max RPM
					(1/60.0) * // Convert to seconds
					(1/motorToWheel)*  // motor to wheel ratio
					360.0); // convert to degrees
	motor3->setOutputBoundingValues(-255, //the minimum value that the output takes (Full reverse)
			255, //the maximum value the output takes (Full forward)
			0, //the value of the output to stop moving
			138, //a positive value added to the stop value to creep backward
			138, //a positive value subtracted from stop value to creep forwards
			16.0 * // Encoder CPR
					50.0 * // Motor Gear box ratio
					1.0 * // motor to arm stage ratio
					(1.0 / 360.0) * // degrees per revolution
					motor3->encoder.countsMode,// Number of edges that are used to increment the value
					117.5 * // Measured max RPM
					(1/60.0) * // Convert to seconds
					360.0); // convert to degrees
	// Set the setpoint the current position in motor units to ensure no motion
	motor1->setSetpoint(motor1->getPosition());
	motor2->setSetpoint(motor2->getPosition());
	motor3->setSetpoint(motor3->getPosition());
	ESP32PWM dummy;
	dummy.getChannel(); // skip the secong 10khz motor
	// Set up digital servo for the gripper
	servo->setPeriodHertz(330);
	servo->attach(SERVO_PIN, 1000, 2000);

	pinMode(LINE_SENSE_ONE, ANALOG);
	pinMode(LINE_SENSE_TWO, ANALOG);
	pinMode(EMITTER_PIN, OUTPUT);
}
/**
 * Seperate from running the motor control,
 * update the state machine for running the final project code here
 */
void StudentsRobot::updateStateMachine() {
	float sigl=0;
	float sigr=0;
	float target = 3000;// the value that the sensors read
	float gain =0.02;
	switch (status) {
	case StartupRobot:
		//Do this once at startup
		status = StartRunning;
		Serial.println("StudentsRobot::updateStateMachine StartupRobot here ");
		break;
	case StartRunning:
		Serial.println("Start Running");
		status = Running;

		break;
	case Running:
		// Do something

		pinMode(LINE_SENSE_ONE, ANALOG);
		pinMode(LINE_SENSE_TWO, ANALOG);

		digitalWrite(EMITTER_PIN, 1);
		delayMicroseconds(500);
		lsensorVal=(float)analogRead(LINE_SENSE_ONE);
		rsensorVal=(float)analogRead(LINE_SENSE_TWO);
		digitalWrite(EMITTER_PIN, 0);
		Serial.print("\r\nPosition = "+String(lsensorVal)+" "+String(rsensorVal)); // comment this line out if you are using raw values
		// print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
		// 1000 means minimum reflectance, followed by the line position

		sigl = (lsensorVal-target)*gain;
		sigr = (rsensorVal-target)*gain;
		if(sigl>0)
			sigl=0;
		if(sigr>0)
				sigr=0;
		Serial.print(" Set = "+String(sigl)+" "+String(sigr));
		motor2->setVelocityDegreesPerSecond(-sigl);
		motor1->setVelocityDegreesPerSecond(-sigr);
		if(sigl==0&&sigr==0)
			status =Halting;

		//Serial.println("Vel 1 is "+String(motor1->getVelocityDegreesPerSecond())+" max "+String(motor1->getFreeSpinMaxDegreesPerSecond()));
		//Serial.println("Vel 2 is "+String(motor2->getVelocityDegreesPerSecond())+" max "+String(motor2->getFreeSpinMaxDegreesPerSecond()));
		//Serial.println("Vel 3 is "+String(motor3->getVelocityDegreesPerSecond())+" max "+String(motor3->getFreeSpinMaxDegreesPerSecond()));


		break;
	case Halting:
		// save state and enter safe mode
		Serial.println("Halting State machine");
		status = Halt;
		break;
	case Halt:
		// in safe mode
		break;

	}
}

/**
 * This is run fast and should return fast
 *
 * You call the PIDMotor's loop function. This will update the whole motor control system
 * This will read from the concoder and write to the motors and handle the hardware interface.
 * Instead of allowing this to be called by the controller yopu may call these from a timer interrupt.
 */
void StudentsRobot::pidLoop() {
	motor1->loop();
	motor2->loop();
	motor3->loop();
}
/**
 * Approve
 *
 * @param buffer A buffer of floats containing nothing
 *
 * the is the event of the Approve button pressed in the GUI
 *
 * This function is called via coms.server() in:
 * @see RobotControlCenter::fastLoop
 */
void StudentsRobot::Approve(float * buffer) {
	// approve the procession to new state
	Serial.println("StudentsRobot::Approve");

	if (myCommandsStatus == Waiting_for_approval_to_pickup) {
		myCommandsStatus = Waiting_for_approval_to_dropoff;
	} else {
		myCommandsStatus = Ready_for_new_task;
	}
}
/**
 * ClearFaults
 *
 * @param buffer A buffer of floats containing nothing
 *
 * this represents the event of the clear faults button press in the gui
 *
 * This function is called via coms.server() in:
 * @see RobotControlCenter::fastLoop
 */
void StudentsRobot::ClearFaults(float * buffer) {
	// clear the faults somehow
	Serial.println("StudentsRobot::ClearFaults");
	myCommandsStatus = Ready_for_new_task;
	status = StartRunning;
}

/**
 * EStop
 *
 * @param buffer A buffer of floats containing nothing
 *
 * this represents the event of the EStop button press in the gui
 *
 * This is called whrn the estop in the GUI is pressed
 * All motors shuld hault and lock in position
 * Motors should not go idle and drop the plate
 *
 * This function is called via coms.server() in:
 * @see RobotControlCenter::fastLoop
 */
void StudentsRobot::EStop(float * buffer) {
	// Stop the robot immediatly
	Serial.println("StudentsRobot::EStop");
	myCommandsStatus = Fault_E_Stop_pressed;
	status = Halting;

}
/**
 * PickOrder
 *
 * @param buffer A buffer of floats containing the pick order data
 *
 * buffer[0]  is the material, aluminum or plastic.
 * buffer[1]  is the drop off angle 25 or 45 degrees
 * buffer[2]  is the drop off position 1, or 2
 *
 * This function is called via coms.server() in:
 * @see RobotControlCenter::fastLoop
 */
void StudentsRobot::PickOrder(float * buffer) {
	float pickupMaterial = buffer[0];
	float dropoffAngle = buffer[1];
	float dropoffPosition = buffer[2];
	Serial.println(
			"StudentsRobot::PickOrder Recived from : " + String(pickupMaterial)
					+ " " + String(dropoffAngle) + " "
					+ String(dropoffPosition));
	myCommandsStatus = Waiting_for_approval_to_pickup;
}
