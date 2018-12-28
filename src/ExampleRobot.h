/*
 * ExampleRobot.h
 *
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#ifndef SRC_EXAMPLEROBOT_H_
#define SRC_EXAMPLEROBOT_H_
#if defined(Arduino_h)
#include <Arduino.h>
#endif
#include "config.h"
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
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

enum state_t {
	Startup,
	WaitForConnect,
	readGame,
	readIMU,
	readIR
	// Add more states here and be sure to add them to the cycle
};
#define numberOfPID  2

class ExampleRobot {
private:
	HBridgeEncoderPIDMotor motor1;  // PID controlled motor object
	HBridgeEncoderPIDMotor motor2; // PID controlled motor object

	// Servo objects
	Servo tiltEyes;
	Servo jaw;
	Servo panEyes;
	// A value to check if enough time has elapsed to tun the sensors and prints
	int64_t lastPrint = 0;
	// Change this to set your team name
	String * name;//
	// List of PID objects to use with PID server
	 PIDMotor * pidList[numberOfPID];// = { &motor1.myPID, &motor2.myPID };

	#if defined(USE_GAME_CONTOL)
	//Wii game pad
	Accessory control;
	#endif
	#if defined(USE_IMU)
	// Simple packet coms server for IMU
	GetIMU * sensor;
	// The IMU object
	Adafruit_BNO055 bno;
	#endif
	#if defined(USE_WIFI)
	// SImple packet coms implementation useing WiFi
	UDPSimplePacket coms;
	// WIfi stack managment state machine
	WifiManager manager;

	#endif
	#if defined(USE_IR_CAM)
	// IR camera
	DFRobotIRPosition myDFRobotIRPosition;
	IRCamSimplePacketComsServer * serverIR;
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
	ExampleRobot(String * name);
	virtual ~ExampleRobot();
	// Pulse the loop function from the main thread
	void loop();
	RobotStatus myStatus = Ready_for_new_task;

};

#endif /* SRC_EXAMPLEROBOT_H_ */
