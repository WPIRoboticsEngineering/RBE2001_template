/*
 * ServoAnalogPIDMotor.h
 *
 *  Created on: Jan 3, 2019
 *      Author: hephaestus
 */

#ifndef SRC_PID_SERVOANALOGPIDMOTOR_H_
#define SRC_PID_SERVOANALOGPIDMOTOR_H_

#include "PIDMotor.h"
#include <ESP32Servo.h>

class ServoAnalogPIDMotor: public PIDMotor {
private:
	Servo motor;
	int adcPin=0;
	int64_t offset=0;
public:
	ServoAnalogPIDMotor();
	/**
	 * Attach the hardware
	 *
	 * @param servoPin the pin number of the Servo PWM
	 * @param analogPin the A channel of the encoder
	 */
	void attach(int servoPin, int analogPin);
	int64_t getPosition();
	int64_t getOutputMin();
	int64_t getOutputMax();
	int64_t getOutputMinDeadbad();
	int64_t getOutputMaxDeadbad();
	int64_t getOutputStop();
	void setOutput(int64_t out);
	void overrideCurrentPositionHardware(int64_t val);
	double calcCur(void);
	double ticksToDeg();
	double getFreeSpinMaxDegreesPerSecond();
};

#endif /* SRC_PID_SERVOANALOGPIDMOTOR_H_ */
