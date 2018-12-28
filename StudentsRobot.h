/*
 * StudentsRobot.h
 *
 *  Created on: Dec 28, 2018
 *      Author: hephaestus
 */

#ifndef STUDENTSROBOT_H_
#define STUDENTSROBOT_H_
#include "src/config.h"
#include <Arduino.h>
class StudentsRobot {
public:
	StudentsRobot();
	RobotStatus myCommandsStatus = Ready_for_new_task;
};

#endif /* STUDENTSROBOT_H_ */
