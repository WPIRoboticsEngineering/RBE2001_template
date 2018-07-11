#if !defined(RBE2001)
#define RBE2001

enum RobotStatus {
	Ready_for_new_task = 0,
	Heading_to_pickup = 1,
	Picking_up = 2,
	Heading_to_Dropoff = 3,
	Dropping_off = 4,
	Heading_to_safe_zone = 5,
	Fault_failed_pickup = 6,
	Fault_failed_dropoff = 7,
	Fault_excessive_load = 8,
	Fault_obstructed_path = 9,
	Fault_E_Stop_pressed = 10
};

#include <robot/MyRobot.h>
#include <commands/ClearFaults.h>
#include <commands/DirectDrive.h>
#include <commands/GetLocation.h>
#include <commands/GetStatus.h>
#include <commands/PickOrder.h>
#include <commands/EStop.h>
#include <Arduino.h>
#include <SimplePacketComs.h>


#endif
