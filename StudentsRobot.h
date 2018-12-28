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
#include "pid/ServoEncoderPIDMotor.h"
#include "pid/HBridgeEncoderPIDMotor.h"
#include <ESP32Servo.h>
enum RobotStateMachine {
	StartupRobot = 0,
	Running=1,
	Halt=3

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
	void pidLoop(HBridgeEncoderPIDMotor * motor1,HBridgeEncoderPIDMotor * motor2, ServoEncoderPIDMotor * motor3);

};

#endif /* STUDENTSROBOT_H_ */
