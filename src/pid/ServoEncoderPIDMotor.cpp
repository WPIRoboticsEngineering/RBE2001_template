/*
 * ServoEncoderPIDMotor.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: hephaestus
 */

#include "ServoEncoderPIDMotor.h"

ServoEncoderPIDMotor::ServoEncoderPIDMotor() {
	setOutputBoundingValues(0, 180, 90, 5, 5,
			16.0 * // Encoder CPR
			50.0 * // Motor Gear box ratio
			1.0 * // motor to wheel stage ratio
			(1.0 / 360.0) * // degrees per revolution
			encoder.countsMode,
			186.0 * 60.0 * 360.0,0);
}

ServoEncoderPIDMotor::~ServoEncoderPIDMotor() {
	// TODO Auto-generated destructor stub
}

void ServoEncoderPIDMotor::attach(int servoPin, int encoderA, int encoderB) {
	encoder.attachHalfQuad(encoderA, encoderB);
	motor.setPeriodHertz(50);
	motor.attach(servoPin, 1000, 2000);
	pidinit();
}

void ServoEncoderPIDMotor::setOutput(int32_t out) {
	motor.write(out);
}
void ServoEncoderPIDMotor::overrideCurrentPositionHardware(int64_t val) {
	encoder.setCount(val);
}
double ServoEncoderPIDMotor::calcCur(void) {
	return 0;
}
int64_t ServoEncoderPIDMotor::getPosition() {
	return encoder.getCount();
}
