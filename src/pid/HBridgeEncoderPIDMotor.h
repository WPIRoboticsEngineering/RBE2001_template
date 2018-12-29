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
	void attach(int pwmPin, int directionPin, int encoderA, int encoderB);
	int64_t getPosition();
	int64_t getOutputMin();
	int64_t getOutputMax();
	int64_t getOutputMinDeadbad();
	int64_t getOutputMaxDeadbad();
	int64_t getOutputStop();
	void setOutput(int64_t out);
	void overrideCurrentPositionHardware(int64_t val);
	ESP32Encoder encoder;
	ESP32PWM motor;
	//This function should analogRead the current sense from the motor driver
	//and convert the value to current in milliamps
	double calcCur(void);
	double ticksToDeg() {
		return 16.0 * // Encoder CPR
				50.0 * // Motor Gear box ratio
				1.0 * // motor to wheel stage ratio
				(1.0 / 360.0) * // degrees per revolution
				encoder.countsMode; // full quadrature, 4 ticks be encoder count, half is 2 and single mode is one

	}
};

#endif /* SRC_HBRIDGEENCODERPIDMOTOR_H_ */
