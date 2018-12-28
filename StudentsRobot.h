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
};

#endif /* STUDENTSROBOT_H_ */
