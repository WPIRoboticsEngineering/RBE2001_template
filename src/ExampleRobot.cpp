/*
 * ExampleRobot.cpp
 *  Remember, Remember the 5th of november
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#include "ExampleRobot.h"

void ExampleRobot::loop() {
	if (esp_timer_get_time() - lastPrint > 500
			|| esp_timer_get_time() < lastPrint // check for the wrap over case
					) {
		switch (state) {
		case Startup:
			setup();
			state = WaitForConnect;
			break;
		case WaitForConnect:
#if defined(USE_WIFI)
			if (manager.getState() == Connected)
#endif
				state = readGame; // begin the main operation loop
			break;
		default:
			break;
		}
		lastPrint = esp_timer_get_time(); // ensure 0.5 ms spacing *between* reads for Wifi to transact
	}
	// If this is run before the sensor reads, the I2C will fail because the time it takes to send the UDP causes a timeout
	fastLoop();    // Run PID and wifi after State machine on all states

}

ExampleRobot::ExampleRobot(String * mn) {
	pidList[0] = &motor1;
	pidList[1] = &motor2;
	state = Startup;
#if defined(	USE_WIFI)
#if defined(USE_IMU)
	sensor = NULL;
#endif
#if defined(USE_IR_CAM)
	serverIR = NULL;
#endif
#endif
	name = mn;
}

ExampleRobot::~ExampleRobot() {
	// TODO Auto-generated destructor stub
}
void ExampleRobot::setupPIDServers(){
#if defined(	USE_WIFI)
	coms.attach(new PIDConfigureSimplePacketComsServer(numberOfPID,pidList));
	coms.attach(new GetPIDData(numberOfPID,pidList));
	coms.attach(new GetPIDConfigureSimplePacketComsServer(numberOfPID,pidList));
#endif

}
void ExampleRobot::setup() {
	if (state != Startup)
		return;
	state = WaitForConnect;
#if defined(USE_WIFI)
	manager.setup();
#else
	Serial.begin(115200);
#endif
	delay(100);
	motor1.attach(MOTOR1_PWM, MOTOR1_DIR, MOTOR1_ENCA, MOTOR1_ENCB);
	motor2.attach(MOTOR2_PWM, MOTOR2_DIR, MOTOR2_ENCA, MOTOR2_ENCB);
	Serial.println("Starting Motors");

	// Set up digital servos
	panEyes.setPeriodHertz(330);
	panEyes.attach(SERVO_PAN, 1000, 2000);
	jaw.setPeriodHertz(330);
	jaw.attach(SERVO_JAW, 1000, 2000);
	tiltEyes.setPeriodHertz(330);
	tiltEyes.attach(SERVO_TILT, 1000, 2000);




#if defined(USE_WIFI)
	// Attach coms
	coms.attach(new NameCheckerServer(name));
	setupPIDServers();
#endif

}

void ExampleRobot::fastLoop() {
	if (state == Startup)    // Do not run before startp
		return;
#if defined(USE_WIFI)
	manager.loop();
	if (manager.getState() == Connected)
		coms.server();
	else {
		return;
	}
#endif

}
