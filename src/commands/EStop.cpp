/*
 * EStop.cpp
 *
 *  Created on: Jul 11, 2018
 *      Author: hephaestus
 */

#include "EStop.h"

void EStop::event(float * buffer){
	robotPointer->EStop(buffer);

}

