/*
 * config.h
 *
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

//#define USE_WIFI

// Pins
/**
 * Drive motor 1 Servo PWM pin
 */
#define MOTOR1_PWM 18
/**
 * Drive motor 2 Servo PWM pin
 */
#define MOTOR2_PWM 16
/**
 * Drive motor 3 10Khz full duty PWM pin
 */
#define MOTOR3_PWM 17
/**
 * Pin for setting the direction of the H-Bridge
 */
#define MOTOR3_DIR 15

//Encoder pins
#define MOTOR1_ENCA 36
#define MOTOR1_ENCB 39

#define MOTOR2_ENCA 34
#define MOTOR2_ENCB 35

#define MOTOR3_ENCA 33
#define MOTOR3_ENCB 26
/**
 * Gripper pin for Servo
 */
#define SERVO_PIN 27

#endif /* SRC_CONFIG_H_ */
