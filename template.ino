#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include <Preferences.h>
#include <WiFi.h>
#include <SimplePacketComs.h>
#include <Esp32SimplePacketComs.h>
#include <wifi/WifiManager.h>
#include <server/NameCheckerServer.h>

#include "src/ExampleRobot.h"

ExampleRobot exampleRobot(new String("IMU-Team21"));
void setup() {
	// let the state machine handle this
}

void loop() {
	exampleRobot.loop();// run the state machine pulse
}
