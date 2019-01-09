/*
 * ServoEncoderPIDMotor.h
 *
 *  Created on: Oct 17, 2018
 *      Author: hephaestus
 */

#ifndef SRC_SERVOENCODERPIDMOTOR_H_
#define SRC_SERVOENCODERPIDMOTOR_H_
#include "PIDMotor.h"
#include <ESP32Servo.h>
#include <ESP32Encoder.h>

class ServoEncoderPIDMotor: public PIDMotor {

public:
	ServoEncoderPIDMotor();
	virtual ~ServoEncoderPIDMotor();
	/**
	 * Attach the hardware
	 *
	 * @param servoPin the pin number of the Servo PWM
	 * @param encoderA the A channel of the encoder
	 * @param encoderB the B channel of the encoder
	 */
	void attach(int servoPin, int encoderA, int encoderB);
	int64_t getPosition();

	void setOutput(int64_t out);
	void overrideCurrentPositionHardware(int64_t val);
	double calcCur(void);
	double ticksToDeg();
	double getFreeSpinMaxDegreesPerSecond();
	ESP32Encoder encoder;
	Servo motor;
};

#endif /* SRC_SERVOENCODERPIDMOTOR_H_ */
