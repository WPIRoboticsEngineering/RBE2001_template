/*
 * GetPIDData.h
 *
 *  Created on: Nov 9, 2018
 *      Author: hephaestus
 */

#ifndef SRC_COMS_GETPIDDATA_H_
#define SRC_COMS_GETPIDDATA_H_
#include <SimplePacketComs.h>
#include "../pid/PIDMotor.h"
class GetPIDData: public PacketEventAbstract {
private:
	PIDMotor ** pidlist;
	int numPID;
public:
	GetPIDData(int num, PIDMotor ** list);
	virtual ~GetPIDData();
	void event(float * buffer);
};

#endif /* SRC_COMS_GETPIDDATA_H_ */
