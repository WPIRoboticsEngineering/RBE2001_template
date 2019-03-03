/*
 * GetPIDVelocity.h
 *
 *  Created on: Mar 3, 2019
 *      Author: hephaestus
 */

#ifndef SRC_COMMANDS_GETPIDVELOCITY_H_
#define SRC_COMMANDS_GETPIDVELOCITY_H_

#include <SimplePacketComs.h>
#include "../pid/PIDMotor.h"
class GetPIDVelocity : public PacketEventAbstract {
private:
	PIDMotor ** pidlist;
	int numPID;
public:
	GetPIDVelocity(int num, PIDMotor ** list);
	virtual ~GetPIDVelocity();
	void event(float * buffer);
};
#endif /* SRC_COMMANDS_GETPIDVELOCITY_H_ */
