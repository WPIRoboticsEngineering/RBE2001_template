/*
 * IRCamSimplePacketComsServer.h
 *
 *  Created on: Oct 19, 2018
 *      Author: hephaestus
 */

#ifndef SRC_COMS_IRCAMSIMPLEPACKETCOMSSERVER_H_
#define SRC_COMS_IRCAMSIMPLEPACKETCOMSSERVER_H_
#include <SimplePacketComs.h>
#include <DFRobotIRPosition.h>

class IRCamSimplePacketComsServer: public PacketEventAbstract {
private:
	DFRobotIRPosition * camera;
	float  bufferCache[8];
public:
	IRCamSimplePacketComsServer(DFRobotIRPosition * cam);
	virtual ~IRCamSimplePacketComsServer();
	void event(float * buffer);
	void loop();
	void print();
};

#endif /* SRC_COMS_IRCAMSIMPLEPACKETCOMSSERVER_H_ */
