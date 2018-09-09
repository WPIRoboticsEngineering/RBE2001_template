/*
 * EStop.cpp
 *
 *  Created on: Jul 11, 2018
 *      Author: hephaestus
 */

#include <commands/EStop.h>

void EStop::event(float * buffer){
	// Stop the robot immediatly
	Serial.println("EStop::event");
	robotPointer->myStatus=Fault_E_Stop_pressed ;

}

