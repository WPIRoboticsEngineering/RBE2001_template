/*
 * HBridgeEncoderPIDMotor.h
 *
 *  Created on: Oct 17, 2018
 *      Author: hephaestus
 */

#ifndef SRC_HBRIDGEENCODERPIDMOTOR_H_
#define SRC_HBRIDGEENCODERPIDMOTOR_H_
#define HBRIDGE_DEADBAND 138
#define HBRIDGE_MAX 255
#include "PIDMotor.h"
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
class HBridgeEncoderPIDMotor: public PIDMotor {
private:

	int directionPin;
public:
	HBridgeEncoderPIDMotor();
	virtual ~HBridgeEncoderPIDMotor();
	/**
	 * Attach the hardware
	 *
	 * @param pwmPin the pin number of the 10 khz PWM
	 * @param directionPin the pin number of the pin used for direction of the H-Bridge
	 * @param encoderA the A channel of the encoder
	 * @param encoderB the B channel of the encoder
	 */
	void attach(int pwmPin, int directionPin, int encoderA, int encoderB);
	int64_t getPosition();
	void setOutput(int64_t out);
	void overrideCurrentPositionHardware(int64_t val);
	ESP32Encoder encoder;
	ESP32PWM motor;
	//This function should analogRead the current sense from the motor driver
	//and convert the value to current in milliamps
	double calcCur(void);
};

#endif /* SRC_HBRIDGEENCODERPIDMOTOR_H_ */
