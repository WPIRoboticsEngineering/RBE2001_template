/*
 * HBridgeEncoderPIDMotor.h
 *
 *  Created on: Oct 17, 2018
 *      Author: hephaestus
 */

#ifndef SRC_HBRIDGEENCODERPIDMOTOR_H_
#define SRC_HBRIDGEENCODERPIDMOTOR_H_
#include "PIDMotor.h"
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
class HBridgeEncoderPIDMotor: public PIDMotor {
private:

	int directionPin;
public:
	HBridgeEncoderPIDMotor();
	virtual ~HBridgeEncoderPIDMotor();
	void attach(int pwmPin, int directionPin, int encoderA, int encoderB);
	int64_t getPosition();
	int64_t getOutputMin();
	int64_t getOutputMax();
	 int64_t getOutputMinDeadbad(){return 133;}
	 int64_t getOutputMaxDeadbad(){return 133;};
	 int64_t getOutputStop(){return 0;};
	void setOutput(int64_t out);
	void overrideCurrentPositionHardware(int64_t val);
	ESP32Encoder encoder;
	ESP32PWM motor;
	//This function should analogRead the current sense from the motor driver
	//and convert the value to current in milliamps
	double calcCur(void);
};

#endif /* SRC_HBRIDGEENCODERPIDMOTOR_H_ */
