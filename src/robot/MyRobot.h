//A robot class to share data between listeners
#include "Arduino.h"

#if !defined(MYROBOT)
#define MYROBOT

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

class MyRobot {
private:
	String * name;
public:
	MyRobot() ;
	void loop();
	String * getName();
};

#endif
