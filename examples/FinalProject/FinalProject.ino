#include <SimplePacketComs.h>
#include <WiiChuck.h>
#include <WiFi.h>
#include <EspWii.h>
#include <ESP32Servo.h>
#include <PacketEvent.h>
#include <RBE2001.h>
#include <Wire.h>

MyRobot robot;
void setup() {
	// Initialize the server mechanism with at least one listener
	launchControllerServer();
	addServer(new ClearFaults(&robot));
	// Add additional servers
	addServer(new PickOrder(&robot));
	// Send and recive bytes instead of floats
	addServer(new GetStatus(&robot));
	// Get the location of the robot
	addServer(new GetLocation(&robot));
	// Direct drive robot command
	addServer(new DirectDrive(&robot));
	setNameUdpDevice(robot.getName());
}

void loop() {
	loopServer();
	robot.loop();
}
