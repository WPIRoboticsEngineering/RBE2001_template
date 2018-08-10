#if !defined(RBE2001)
#define RBE2001

enum RobotStatus {
	Ready_for_new_task = 0,
	Heading_to_pickup = 1,
	Waiting_for_approval_to_pickup = 2,
	Picking_up = 3,
	Heading_to_Dropoff = 4,
	Dropping_off = 5,
	Heading_to_safe_zone = 6,
	Fault_failed_pickup = 7,
	Fault_failed_dropoff = 8,
	Fault_excessive_load = 9,
	Fault_obstructed_path = 10,
	Fault_E_Stop_pressed = 11
};

#include <robot/MyRobot.h>
#include <commands/ClearFaults.h>
#include <commands/GetStatus.h>
#include <commands/PickOrder.h>
#include <commands/Approve.h>
#include <commands/EStop.h>
#include <Arduino.h>
#include <SimplePacketComs.h>


#endif
