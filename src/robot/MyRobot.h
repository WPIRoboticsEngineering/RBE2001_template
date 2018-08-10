//A robot class to share data between listeners
#include "Arduino.h"
#include "RBE2001.h"
#if !defined(MYROBOT)
#define MYROBOT

class MyRobot {
private:
	String * name;
public:
	enum RobotStatus myStatus;

	MyRobot() ;
	void loop();
	String * getName();
};

#endif
