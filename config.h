 /*
 * config.h
 *
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

#define TEAM_NAME "IMU-Team21"

#define USE_WIFI

#define WHEEL_TRACK 175.0
#define WHEEL_RADIUS (2.0*25.4/2.0)

// Pins
/**
 * Drive motor 1 Servo PWM pin
 */
#define MOTOR1_PWM 5
/**
 * Drive motor 2 Servo PWM pin
 */
#define MOTOR2_PWM 15
/**
 * Drive motor 3 10Khz full duty PWM pin
 */
#define MOTOR3_PWM 12
/**
 * Pin for setting the direction of the H-Bridge
 */
#define MOTOR3_DIR 26

//Encoder pins
#define MOTOR1_ENCA 19
#define MOTOR1_ENCB 18

#define MOTOR2_ENCA 17
#define MOTOR2_ENCB 16

#define MOTOR3_ENCA 14
#define MOTOR3_ENCB 27
// Line Sensor Pins
#define LINE_SENSE_ONE 			36
#define LINE_SENSE_TWO 			39
#define EMITTER_PIN             13  // emitter is controlled by digital pin



/**
 * Gripper pin for Servo
 */
#define SERVO_PIN 23

#endif /* SRC_CONFIG_H_ */
