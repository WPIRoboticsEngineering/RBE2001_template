#include "RBE2001.h"

MyRobot::MyRobot() {
	//Put initialization code here
	name = new String("Warehouse-21");
	myStatus=Ready_for_new_task;

}
void MyRobot::loop() {
	//put loop code here
}
String * MyRobot::getName() {
	return name;
}
