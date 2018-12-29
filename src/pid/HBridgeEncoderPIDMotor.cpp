/*
 * HBridgeEncoderPIDMotor.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: hephaestus
 */

#include "HBridgeEncoderPIDMotor.h"

HBridgeEncoderPIDMotor::HBridgeEncoderPIDMotor() {
	// TODO Auto-generated constructor stub
	this->directionPin = -1;
}

HBridgeEncoderPIDMotor::~HBridgeEncoderPIDMotor() {
	// TODO Auto-generated destructor stub
}

void HBridgeEncoderPIDMotor::attach(int pwmPin, int directionPin, int encoderA,
		int encoderB) {
	encoder.attachHalfQuad(encoderA, encoderB);
	this->directionPin = directionPin;
	motor.attachPin(pwmPin, 10000, 8);
	pidinit();
	pinMode(directionPin, OUTPUT);
	setOutput(0);
}
int64_t HBridgeEncoderPIDMotor::getPosition() {
	return encoder.getCount();
}
int64_t HBridgeEncoderPIDMotor::getOutputMin() {
	return -HBRIDGE_MAX;
}
int64_t HBridgeEncoderPIDMotor::getOutputMax() {
	return HBRIDGE_MAX;
}
int64_t HBridgeEncoderPIDMotor::getOutputMinDeadbad() {
	return HBRIDGE_DEADBAND;
}
int64_t HBridgeEncoderPIDMotor::getOutputMaxDeadbad() {
	return HBRIDGE_DEADBAND;
}
int64_t HBridgeEncoderPIDMotor::getOutputStop() {
	return 0;
}
void HBridgeEncoderPIDMotor::setOutput(int64_t out) {
	if (out > 0) {
		digitalWrite(directionPin, HIGH); // turn the LED on (HIGH is the voltage level)
	} else {
		digitalWrite(directionPin, LOW);
	}
	int myOut = abs(out);
	if (myOut < HBRIDGE_DEADBAND && out != 0)
		myOut = HBRIDGE_DEADBAND;

	motor.write(myOut);
}
void HBridgeEncoderPIDMotor::overrideCurrentPositionHardware(int64_t val) {
	encoder.setCount(val);
}
//This function should analogRead the current sense from the motor driver
//and convert the value to current in milliamps
double HBridgeEncoderPIDMotor::calcCur(void) {
	//read analog value
	//convert to volts
	//converts to current in milliamps
	return 0;
}

double HBridgeEncoderPIDMotor::ticksToDeg() {
	return 16.0 * // Encoder CPR
			50.0 * // Motor Gear box ratio
			1.0 * // motor to wheel stage ratio
			(1.0 / 360.0) * // degrees per revolution
			encoder.countsMode; // full quadrature, 4 ticks be encoder count, half is 2 and single mode is one

}
double HBridgeEncoderPIDMotor::getFreeSpinMaxDegreesPerSecond(){
	return 186.0*60.0*360.0;
}
