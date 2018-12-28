#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include <Wire.h>
#include <WiiChuck.h>
#include <Preferences.h>
#include <WiFi.h>
#include <SimplePacketComs.h>
#include <Esp32SimplePacketComs.h>
#include <wifi/WifiManager.h>
#include <server/NameCheckerServer.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <BNO055SimplePacketComs.h>
#include <DFRobotIRPosition.h>
#include <SPI.h>

#include "src/ExampleRobot.h"

ExampleRobot exampleRobot(new String("IMU-Team21"));
void setup() {
	// let the state machine handle this
}

void loop() {
	exampleRobot.loop();// run the state machine pulse
}
