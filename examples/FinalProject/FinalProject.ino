#include <Preferences.h>
#include <SimplePacketComs.h>
#include <WiFi.h>
#include <Esp32SimplePacketComs.h>
#include <ESP32Servo.h>
#include <PacketEvent.h>
#include <RBE2001.h>
#include <Wire.h>

MyRobot * robotPointer;
void setup() {
	// Initialize the server mechanism
	launchControllerServer();
	robotPointer = new MyRobot();
	//Estop command
	addServer((PacketEventAbstract *)new EStop(robotPointer));
	// clear any fault command
	addServer((PacketEventAbstract *)new ClearFaults(robotPointer));
	// Pick up an panel command
	addServer((PacketEventAbstract *)new PickOrder(robotPointer));
	// Get the status of the robot
	addServer((PacketEventAbstract *)new GetStatus(robotPointer));
	// Approve a procede command from the controller
	addServer((PacketEventAbstract *)new Approve(robotPointer));
	// Set the name of the robot for the UDP server
	setNameUdpDevice(robotPointer->getName());
}

void loop() {
	loopServer();
	robotPointer->loop();
}
