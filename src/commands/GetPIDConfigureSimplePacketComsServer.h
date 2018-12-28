/*
 * PIDConfigureSimplePacketComsServer.h
 *
 *  Created on: Oct 19, 2018
 *      Author: hephaestus
 */

#ifndef SRC_COMSGet_PIDCONFIGURESIMPLEPACKETCOMSSERVER_H_
#define SRC_COMGetS_PIDCONFIGURESIMPLEPACKETCOMSSERVER_H_
#include <SimplePacketComs.h>
#include "../pid/PIDMotor.h"
class GetPIDConfigureSimplePacketComsServer: public PacketEventAbstract {
	PIDMotor ** pidlist;
	int numPID;
public:
	GetPIDConfigureSimplePacketComsServer(int num,PIDMotor ** list);
	void event(float * buffer);

};

#endif /* SRC_COMS_PIDCONFIGURESIMPLEPACKETCOMSSERVER_H_ */
