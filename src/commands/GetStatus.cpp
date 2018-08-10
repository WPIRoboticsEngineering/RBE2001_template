#include "GetStatus.h"

void GetStatus::event(float * buffer) {
	uint8_t * bytes = (uint8_t *) buffer;
	int numberOfBytes = 60;
	// This command is totally done unless you choose not to use robotPointer->myStatus
	bytes[0]=robotPointer->myStatus;// your robots current status
	for (int i = 1; i < numberOfBytes; i++) {
		bytes[i] = 0;	// zero out the packet
	}
}
