#include "GetStatus.h"

void GetStatus::event(float * buffer) {
	uint8_t * bytes = (uint8_t *) buffer;
	int numberOfBytes = 60;
	bytes[0]=0;// something like this... robotPointer->status;
	for (int i = 1; i < numberOfBytes; i++) {
		bytes[i] = 0;	// write a value to the controller
	}
}
