/*
 * SetPIDVelocity.h
 *
 *  Created on: Mar 3, 2019
 *      Author: hephaestus
 */

#ifndef SRC_COMMANDS_SETPIDVELOCITY_H_
#define SRC_COMMANDS_SETPIDVELOCITY_H_
#include <SimplePacketComs.h>
#include "../pid/PIDMotor.h"
class SetPIDVelocity : public PacketEventAbstract {
private:
	PIDMotor ** pidlist;
	int numPID;
public:
	SetPIDVelocity(int num, PIDMotor ** list);
	virtual ~SetPIDVelocity();
	void event(float * buffer);
};

#endif /* SRC_COMMANDS_SETPIDVELOCITY_H_ */
