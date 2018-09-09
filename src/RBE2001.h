#if !defined(RBE2001)
#define RBE2001

enum RobotStatus {
	Ready_for_new_task = 0,
	Heading_to_pickup = 1,
	Waiting_for_approval_to_pickup = 2,
	Picking_up = 3,
	Heading_to_Dropoff = 4,
	Waiting_for_approval_to_dropoff = 5,
	Dropping_off = 6,
	Heading_to_safe_zone = 7,
	Fault_failed_pickup = 8,
	Fault_failed_dropoff = 9,
	Fault_excessive_load = 10,
	Fault_obstructed_path = 11,
	Fault_E_Stop_pressed = 12
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
