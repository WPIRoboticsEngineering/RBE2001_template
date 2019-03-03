/*
 * GetPDVelocityConstants.h
 *
 *  Created on: Mar 3, 2019
 *      Author: hephaestus
 */

#ifndef SRC_COMMANDS_GETPDVELOCITYCONSTANTS_H_
#define SRC_COMMANDS_GETPDVELOCITYCONSTANTS_H_
#include <SimplePacketComs.h>
#include "../pid/PIDMotor.h"
class  GetPDVelocityConstants: public PacketEventAbstract {
private:
	PIDMotor ** pidlist;
	int numPID;
public:
	GetPDVelocityConstants(int num, PIDMotor ** list);
	virtual ~GetPDVelocityConstants();
	void event(float * buffer);
};
#endif /* SRC_COMMANDS_GETPDVELOCITYCONSTANTS_H_ */
