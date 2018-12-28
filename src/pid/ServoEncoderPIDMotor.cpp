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

void ServoEncoderPIDMotor::attach(int servoPin,int encoderA, int encoderB){
	encoder.attachHalfQuad(encoderA, encoderB);
	motor.setPeriodHertz(330);
	motor.attach(servoPin, 1000, 2000);
	pidinit();
}
int64_t ServoEncoderPIDMotor::getPosition(){
	return encoder.getCount();
}
int64_t ServoEncoderPIDMotor::getOutputMin(){
	return 0;
}
int64_t ServoEncoderPIDMotor::getOutputMax(){
	return 180;
}
void ServoEncoderPIDMotor::setOutput(int64_t out){
	motor.write(out);
}
void ServoEncoderPIDMotor::overrideCurrentPositionHardware(int64_t val){
	encoder.setCount(val);
}
