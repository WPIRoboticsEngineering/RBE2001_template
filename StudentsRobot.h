/*
 * StudentsRobot.h
 *
 *  Created on: Dec 28, 2018
 *      Author: hephaestus
 */

#ifndef STUDENTSROBOT_H_
#define STUDENTSROBOT_H_
#include "config.h"
#include <Arduino.h>
#include "src/pid/ServoEncoderPIDMotor.h"
#include "src/pid/HBridgeEncoderPIDMotor.h"
#include <ESP32Servo.h>
enum RobotStateMachine {
	StartupRobot = 0,
	StartRunning=1,
	Running=2,
	Halting=3,
	Halt=4

};
class StudentsRobot {
public:
	StudentsRobot();
	RobotStatus myCommandsStatus = Ready_for_new_task;
	RobotStateMachine status=StartupRobot;
	void Approve(float * data);
	void ClearFaults(float * data);
	void EStop(float * buffer);
	void PickOrder(float * buffer) ;
	void attach(HBridgeEncoderPIDMotor * motor1,HBridgeEncoderPIDMotor * motor2, ServoEncoderPIDMotor * motor3, Servo * servo);
	void pidLoop(PIDMotor * motor1,PIDMotor * motor2, PIDMotor * motor3);
	void updateStateMachine(PIDMotor * motor1,
			PIDMotor * motor2,PIDMotor * motor3,
			Servo * servo);
};

#endif /* STUDENTSROBOT_H_ */
