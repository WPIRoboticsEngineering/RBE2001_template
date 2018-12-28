#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include <Preferences.h>
#include <WiFi.h>
#include <SimplePacketComs.h>
#include <Esp32SimplePacketComs.h>
#include <wifi/WifiManager.h>
#include <server/NameCheckerServer.h>

#include "src/ExampleRobot.h"

ExampleRobot * exampleRobot;
void setup() {
	exampleRobot=new ExampleRobot(new String("IMU-Team21"));
}

void loop() {
	exampleRobot->loop();// run the state machine pulse
}
