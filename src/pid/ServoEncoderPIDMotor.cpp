/*
 * ServoEncoderPIDMotor.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: hephaestus
 */

#include "ServoEncoderPIDMotor.h"

ServoEncoderPIDMotor::ServoEncoderPIDMotor() {
	// TODO Auto-generated constructor stub

}

ServoEncoderPIDMotor::~ServoEncoderPIDMotor() {
	// TODO Auto-generated destructor stub
}

void ServoEncoderPIDMotor::attach(int servoPin, int encoderA, int encoderB) {
	encoder.attachHalfQuad(encoderA, encoderB);
	motor.setPeriodHertz(330);
	motor.attach(servoPin, 1000, 2000);
	pidinit();
}
int64_t ServoEncoderPIDMotor::getPosition() {
	return encoder.getCount();
}
int64_t ServoEncoderPIDMotor::getOutputMin() {
	return 0;
}
int64_t ServoEncoderPIDMotor::getOutputMax() {
	return 180;
}
int64_t ServoEncoderPIDMotor::getOutputMinDeadbad() {
	return 5;
}
int64_t ServoEncoderPIDMotor::getOutputMaxDeadbad() {
	return 5;
}
int64_t ServoEncoderPIDMotor::getOutputStop() {
	return 90;
}
void ServoEncoderPIDMotor::setOutput(int64_t out) {
	motor.write(out);
}
void ServoEncoderPIDMotor::overrideCurrentPositionHardware(int64_t val) {
	encoder.setCount(val);
}
double ServoEncoderPIDMotor::ticksToDeg() {
	return 16.0 * // Encoder CPR
			50.0 * // Motor Gear box ratio
			1.0 * // motor to wheel stage ratio
			(1.0 / 360.0) * // degrees per revolution
			encoder.countsMode; // full quadrature, 4 ticks be encoder count, half is 2 and single mode is one

}
double ServoEncoderPIDMotor::calcCur(void) {
	return 0;
}
double ServoEncoderPIDMotor::getFreeSpinMaxDegreesPerSecond(){
	return 186.0*60.0*360.0;
}
