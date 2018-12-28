/*
 * Messages.h
 *
 *  Created on: 10/1/16
 *      Author: joest
 */

#include "LookupTable.h"
#include "Arduino.h"

//array of torques based off current and RPM.
//Review the provided excel document for a better understanding. 
const float torqueArray[11][11] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 6.3 }, { 0, 0, 0, 0, 0, 0, 2.52, 5.04, 7.56,
		10.08, 12.6 }, { 0, 0, 0, 0, 2.7, 5.4, 8.1, 10.8, 13.5, 16.2, 18.9 }, {
		0, 0, 0, 3.15, 6.3, 9.45, 12.6, 15.75, 18.9, 22.05, 25.2 }, { 0, 0, 3.5,
		7, 10.5, 14, 17.5, 21, 24.5, 28, 31.5 }, { 0, 0, 4.2, 8.4, 12.6, 16.8,
		21, 25.2, 29.4, 33.6, 37.8 }, { 0, 0, 4.9, 9.8, 14.7, 19.6, 24.5, 29.4,
		34.3, 39.2, 44.1 }, { 0, 5.04, 10.08, 15.12, 20.16, 25.2, 30.24, 35.28,
		40.32, 45.36, 50.4 }, { 0, 5.67, 11.34, 17.01, 22.68, 28.35, 34.02,
		39.69, 45.36, 51.03, 56.7 }, { 0, 6.3, 12.6, 18.9, 25.2, 31.5, 37.8,
		44.1, 50.4, 56.7, 63 }

};

//Class constructor
Lookup::Lookup() {

}

//Function that finds the row and colum of the torque based
//off the current in milliamps and the RPM
float Lookup::torque(float current, float rpm) {
	int x = 0;
	int y = 0;
	// Sets the row based on current reading
	if (current >= 0 && current < 219) {
		x = 0;
	}
	if (current > 220 && current < 439) {
		x = 1;
	}
	if (current > 440 && current < 659) {
		x = 2;
	}
	if (current > 660 && current < 879) {
		x = 3;
	}
	if (current > 880 && current < 1099) {
		x = 4;
	}
	if (current > 1100 && current < 1319) {
		x = 5;
	}
	if (current > 1320 && current < 1539) {
		x = 6;
	}
	if (current > 1540 && current < 1759) {
		x = 7;
	}
	if (current > 1760 && current < 1979) {
		x = 8;
	}
	if (current > 1980 && current < 2199) {
		x = 9;
	}
	if (current > 2200) {
		x = 10;
	}

	//Sets the column based off RPM
	if (rpm < 300 && rpm > 200) {
		y = 0;
	}
	if (rpm < 199 && rpm > 180) {
		y = 1;
	}
	if (rpm < 179 && rpm > 160) {
		y = 2;
	}
	if (rpm < 159 && rpm > 140) {
		y = 3;
	}
	if (rpm < 139 && rpm > 120) {
		y = 4;
	}
	if (rpm < 119 && rpm > 100) {
		y = 5;
	}
	if (rpm < 99 && rpm > 80) {
		y = 6;
	}
	if (rpm < 79 && rpm > 60) {
		y = 7;
	}
	if (rpm < 59 && rpm > 40) {
		y = 8;
	}
	if (rpm < 39 && rpm > 20) {
		y = 9;
	}
	if (rpm < 19 && rpm >= 0) {
		y = 10;
	}
	//returns the torque from the lookup table

	float torq = torqueArray[x][y];
	return torq;
}
