#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include <Preferences.h>
#include <WiFi.h>
#include <SimplePacketComs.h>
#include <Esp32SimplePacketComs.h>
#include <wifi/WifiManager.h>
#include <server/NameCheckerServer.h>

#include "src/RobotControlCenter.h"

RobotControlCenter * exampleRobot;
void setup() {
	exampleRobot=new RobotControlCenter(new String("IMU-Team21"));
}

void loop() {
	exampleRobot->loop();// run the state machine pulse
}
