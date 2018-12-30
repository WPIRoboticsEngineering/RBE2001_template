/*
 * ExampleRobot.h
 *
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#ifndef SRC_ROBOTCONTROLCENTER_H_
#define SRC_ROBOTCONTROLCENTER_H_

#if defined(Arduino_h)
#include <Arduino.h>
#endif
#include "../config.h"
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
#include "commands/GetPIDConstants.h"
#include "commands/GetPIDData.h"
#include "commands/SetPIDConstants.h"
#include "commands/SetPIDSetpoint.h"
#include "commands/Approve.h"
#include "commands/ClearFaults.h"
#include "commands/EStop.h"
#include "commands/GetStatus.h"
#include "commands/PickOrder.h"
#include "../StudentsRobot.h"
enum state_t {
	Startup, WaitForConnect, run
// Add more states here and be sure to add them to the cycle
};
#define numberOfPID  3
/**
 * RobotControlCenter is the main class for the 2000 level student code
 *
 * This class is the starting point for all the code. Student code is
 * housed in StudentsRobot class
 * @see StudentsRobot
 *
 * This class managed the overall state machine for dealing with connecting and
 * maintaining connection to the WiFi, constructing the StudentsRobot class, and managing
 * the StudentsRobot calls to updates its state machine as well as its PID loops.
 *
 */
class RobotControlCenter {
private:
	HBridgeEncoderPIDMotor motor1;  // PID controlled motor object
	HBridgeEncoderPIDMotor motor2; // PID controlled motor object
	ServoEncoderPIDMotor motor3; // PID controlled motor object
	// Servo objects
	Servo servo;
	// A value to check if enough time has elapsed to tun the sensors and prints
	int64_t lastPrint = 0;
	// Change this to set your team name
	String * name;	//
	// List of PID objects to use with PID server
	PIDMotor * pidList[numberOfPID];	// = { &motor1.myPID, &motor2.myPID };

#if defined(USE_WIFI)
	// SImple packet coms implementation useing WiFi
	UDPSimplePacket coms;
	// WIfi stack managment state machine
	WifiManager manager;

#endif

	// The fast loop actions
	// This should be run every loop and is internally gated for fast opperation
	void fastLoop();
	// Internal setup function. set up all objects
	void setup();
	//attach the PID servers
	void setupPIDServers();
	// State machine state
	state_t state = Startup;
public:
	/**
	 * RobotControlCenter constructor
	 *
	 * The name is used bt the SimplePacketComs stack to locate your specific
	 * robot on the network.
	 */
	RobotControlCenter(String * name);
	~RobotControlCenter() {
	}
	/**
	 * Pulse the loop function from the main thread
	 *
	 * This function is callled over and over by the INO loop()
	 */
	void loop();
	/**
	 * A pointer to the students robot
	 *
	 * NULL at startup, this is instantiated by the RobotControlCenter state machine.
	 */
	StudentsRobot * robot;

};

#endif /* SRC_ROBOTCONTROLCENTER_H_ */
