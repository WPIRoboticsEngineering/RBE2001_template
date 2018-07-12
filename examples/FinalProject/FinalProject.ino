#include <SimplePacketComs.h>
#include <WiFi.h>
#include <Esp32SimplePacketComs.h>
#include <ESP32Servo.h>
#include <PacketEvent.h>
#include <RBE2001.h>
#include <Wire.h>

MyRobot robot;
void setup() {
	// Initialize the server mechanism with at least one listener
	launchControllerServer();
	//Estop command
	addServer(new EStop(&robot));
	// clear any fault command
	addServer(new ClearFaults(&robot));
	// Pick up an panel command
	addServer(new PickOrder(&robot));
	// Get the status of the robot
	addServer(new GetStatus(&robot));
	// Get the location of the robot
	addServer(new GetLocation(&robot));
	// Direct drive robot command
	addServer(new DirectDrive(&robot));
	// Set the name of the robot for the UDP server
	setNameUdpDevice(robot.getName());
}

void loop() {
	loopServer();
	robot.loop();
}
