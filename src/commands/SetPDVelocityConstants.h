/*
 * SetPDVelocityConstants.h
 *
 *  Created on: Mar 3, 2019
 *      Author: hephaestus
 */

#ifndef SRC_COMMANDS_SETPDVELOCITYCONSTANTS_H_
#define SRC_COMMANDS_SETPDVELOCITYCONSTANTS_H_
#include <SimplePacketComs.h>
#include "../pid/PIDMotor.h"
class SetPDVelocityConstants : public PacketEventAbstract {
private:
	PIDMotor ** pidlist;
	int numPID;
public:
	SetPDVelocityConstants(int num, PIDMotor ** list);
	virtual ~SetPDVelocityConstants();
	void event(float * buffer);
};
#endif /* SRC_COMMANDS_SETPDVELOCITYCONSTANTS_H_ */
