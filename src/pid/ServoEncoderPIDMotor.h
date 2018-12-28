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
private:
	ESP32Encoder encoder;
	Servo motor;
public:
	ServoEncoderPIDMotor();
	virtual ~ServoEncoderPIDMotor();
	void attach(int servoPin, int encoderA, int encoderB);
	int64_t getPosition();
	int64_t getOutputMin();
	int64_t getOutputMax();
	void setOutput(int64_t out);
	void overrideCurrentPositionHardware(int64_t val);
	double calcCur(void) {
		return 0;
	}
	;

};

#endif /* SRC_SERVOENCODERPIDMOTOR_H_ */
