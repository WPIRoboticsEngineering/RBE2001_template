/*
 * ServoAnalogPIDMotor.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: hephaestus
 */

#include "ServoAnalogPIDMotor.h"
#include <esp32-hal-gpio.h>
ServoAnalogPIDMotor::ServoAnalogPIDMotor() {
	// TODO Auto-generated constructor stub

}

void ServoAnalogPIDMotor::attach(int servoPin, int analogPin) {
	if(digitalPinToAnalogChannel(analogPin)<1){
		Serial.println("Pin can not be ADC! "+String(analogPin));
		while (1);
	}
	adcPin=analogPin;
	motor.setPeriodHertz(330);
	motor.attach(servoPin, 1000, 2000);
	pidinit();
	pinMode(adcPin, ANALOG);
	filterSum=(float)analogRead(adcPin)*filterSize;
	for(int i=0;i<filterSize;i++){
		filterBuffer[filterIndex]=(float)analogRead(adcPin);
		getPosition();
	}
}
int64_t ServoAnalogPIDMotor::getPosition() {
	pinMode(adcPin, ANALOG);
	float current =  (float)analogRead(adcPin);
	filterSum-=filterBuffer[filterIndex];
	filterBuffer[filterIndex]= current;
	filterSum+=filterBuffer[filterIndex];
	filterIndex++;
	if(filterIndex==filterSize)
		filterIndex=0;
	int64_t computedAvg =(int64_t) (filterSum/((float)filterSize));

	return computedAvg+offset;
}
int64_t ServoAnalogPIDMotor::getOutputMin() {
	return 0;
}
int64_t ServoAnalogPIDMotor::getOutputMax() {
	return 180;
}
int64_t ServoAnalogPIDMotor::getOutputMinDeadbad() {
	return 5;
}
int64_t ServoAnalogPIDMotor::getOutputMaxDeadbad() {
	return 5;
}
int64_t ServoAnalogPIDMotor::getOutputStop() {
	return 90;
}
void ServoAnalogPIDMotor::setOutput(int64_t out) {
	motor.write(out);
}
void ServoAnalogPIDMotor::overrideCurrentPositionHardware(int64_t val) {
	offset = val-(getPosition()-offset);
}
double ServoAnalogPIDMotor::ticksToDeg() {
	return 270.0/ //degrees in range
			(3.3/4096.0); // ticks to volts

}
double ServoAnalogPIDMotor::calcCur(void) {
	return 0;
}
double ServoAnalogPIDMotor::getFreeSpinMaxDegreesPerSecond() {
	return 186.0 * 60.0 * 360.0;
}
