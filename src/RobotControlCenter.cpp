/*
 * ExampleRobot.cpp
 *  Remember, Remember the 5th of november
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#include "RobotControlCenter.h"

void RobotControlCenter::loop() {
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
				state = run; // begin the main operation loop
			break;
		default:
			break;
		}
		lastPrint = esp_timer_get_time(); // ensure 0.5 ms spacing *between* reads for Wifi to transact
	}
	if (state != Startup) {
		// If this is run before the sensor reads, the I2C will fail because the time it takes to send the UDP causes a timeout
		fastLoop();    // Run PID and wifi after State machine on all states
	}

}

RobotControlCenter::RobotControlCenter(String * mn) {
	pidList[0] = &motor1;
	pidList[1] = &motor2;
	pidList[2] = &motor3;
	state = Startup;
	name = mn;
	robot = NULL;
}

void RobotControlCenter::setup() {
	if (state != Startup)
		return;
	state = WaitForConnect;
#if defined(USE_WIFI)
	manager.setup();
#else
	Serial.begin(115200);
#endif

	motor1.attach(MOTOR1_PWM, MOTOR1_DIR, MOTOR1_ENCA, MOTOR1_ENCB);
	motor2.attach(MOTOR2_PWM, MOTOR2_DIR, MOTOR2_ENCA, MOTOR2_ENCB);
	motor3.attach(MOTOR3_PWM, MOTOR3_DIR, MOTOR3_ENCA, MOTOR3_ENCB);
	// Set the setpoint the current position in motor units to ensure no motion
	motor1.setSetpoint(motor1.getPosition());
	motor2.setSetpoint(motor2.getPosition());
	motor3.setSetpoint(motor3.getPosition());

	// Set up digital servo for the gripper
	servo.setPeriodHertz(50);
	servo.attach(SERVO_PIN, 1000, 2000);
	robot = new StudentsRobot(&motor1, &motor2, &motor3, &servo);


#if defined(USE_WIFI)
	// Attach coms
	coms.attach(new NameCheckerServer(name)); // @suppress("Method cannot be resolved")
	coms.attach(new SetPIDSetpoint(numberOfPID, pidList)); // @suppress("Method cannot be resolved")
	coms.attach(new SetPIDConstants(numberOfPID, pidList)); // @suppress("Method cannot be resolved")
	coms.attach(new GetPIDData(numberOfPID, pidList)); // @suppress("Method cannot be resolved")
	coms.attach( // @suppress("Method cannot be resolved")
			new GetPIDConstants(numberOfPID, pidList));
	coms.attach(new GetPIDVelocity(numberOfPID, pidList));
	coms.attach(new GetPDVelocityConstants(numberOfPID, pidList));
	coms.attach(new SetPIDVelocity(numberOfPID, pidList));
	coms.attach(new SetPDVelocityConstants(numberOfPID, pidList));

	coms.attach(new EStop(robot)); // @suppress("Method cannot be resolved")
	// clear any fault command
	coms.attach(new ClearFaults(robot));// @suppress("Method cannot be resolved")
	// Pick up an panel command
	coms.attach(new PickOrder(robot));// @suppress("Method cannot be resolved")
	// Get the status of the robot
	coms.attach(new GetStatus(robot));// @suppress("Method cannot be resolved")
	// Approve a procede command from the controller
	coms.attach(new Approve(robot));// @suppress("Method cannot be resolved")
#endif

}

void RobotControlCenter::fastLoop() {
	if (state == Startup)    // Do not run before startp
		return;
#if defined(USE_WIFI)
	manager.loop();
	if (manager.getState() == Connected)
		coms.server(); // @suppress("Method cannot be resolved")
	else {
		return;
	}
#endif
	robot->pidLoop();
	robot->updateStateMachine();

}
