/*
 * ExampleRobot.h
 *
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#ifndef SRC_ABSTRACTROBOT_H_
#define SRC_ABSTRACTROBOT_H_
#if defined(Arduino_h)
#include <Arduino.h>
#endif
#include "config.h"
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include "../RBEPID.h"
#include "pid/PIDMotor.h"
#include "pid/ServoEncoderPIDMotor.h"
#include "pid/HBridgeEncoderPIDMotor.h"
#include <Preferences.h>
#include <WiFi.h>
#include <SimplePacketComs.h>
#include <Esp32SimplePacketComs.h>
#include <wifi/WifiManager.h>
#include <server/NameCheckerServer.h>
#include "commands/GetPIDConfigureSimplePacketComsServer.h"
#include "commands/GetPIDData.h"
#include "commands/PIDConfigureSimplePacketComsServer.h"

#include "commands/Approve.h"
#include "commands/ClearFaults.h"
#include "commands/EStop.h"
#include "commands/GetStatus.h"
#include "commands/PickOrder.h"
#include "../StudentsRobot.h"
enum state_t {
	Startup,
	WaitForConnect,
	run
	// Add more states here and be sure to add them to the cycle
};
#define numberOfPID  3

class AbstractRobot {
private:
	HBridgeEncoderPIDMotor motor1;  // PID controlled motor object
	HBridgeEncoderPIDMotor motor2; // PID controlled motor object
	ServoEncoderPIDMotor   motor3; // PID controlled motor object
	// Servo objects
	Servo servo;
	// A value to check if enough time has elapsed to tun the sensors and prints
	int64_t lastPrint = 0;
	// Change this to set your team name
	String * name;//
	// List of PID objects to use with PID server
	PIDMotor * pidList[numberOfPID];// = { &motor1.myPID, &motor2.myPID };

	#if defined(USE_WIFI)
	// SImple packet coms implementation useing WiFi
	UDPSimplePacket coms;
	// WIfi stack managment state machine
	WifiManager manager;

	#endif

	// RUn the game control logic
	void runGameControl();
	// Print the values of the robot
	void printAll();
	// The fast loop actions
	// This should be run every loop and is internally gated for fast opperation
	void fastLoop();
	// Internal setup function. set up all objects
	void setup();
	//attach the PID servers
	void setupPIDServers();
	// State machine state
	state_t state=Startup;
public:
	AbstractRobot(String * name);
	 ~AbstractRobot(){}
	// Pulse the loop function from the main thread
	void loop();
	StudentsRobot * robot;

};

#endif /* SRC_ABSTRACTROBOT_H_ */
