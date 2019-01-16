/*
 * DrivingChassis.h
 *
 *  Created on: Jan 12, 2019
 *      Author: hephaestus
 */

#ifndef DRIVINGCHASSIS_H_
#define DRIVINGCHASSIS_H_
#include "src/pid/PIDMotor.h"
/**
 * DrivingChassis encapsulates a 2 wheel differential steered chassis that drives around
 *
 * The 0,0,0 center of the robot is on the ground, half way between the left and right wheel contact points.
 *
 * The +X axis is the positive direction of travel
 *
 * The +Y axis goes from the center of the robot to the left wheel
 *
 * The +Z axis goes from the center up through the robot towards the ceiling.
 *
 * This object should manage the setting of motor setpoints to enable driving
 */
class DrivingChassis {
private:
	PIDMotor * myleft;
	PIDMotor * myright;
	float mywheelTrackMM;
	float mywheelRadiusMM;
	/**
	 * Compute a delta in wheel angle to traverse a specific distance
	 *
	 * arc length	=	2*	π*	R*	(C/360)
	 *
	 * C  is the central angle of the arc in degrees
	 * R  is the radius of the arc
	 * π  is Pi
	 *
	 * @param distance a distance for this wheel to travel in MM
	 * @return the wheel angle delta in degrees
	 */
	float distanceToWheelAngle(float distance);
	/**
	 * Compute the arch length distance the wheel needs to travel through to rotate the base
	 * through a given number of degrees.
	 *
	 * arc length	=	2*	π*	R*	(C/360)
	 *
	 * C  is the central angle of the arc in degrees
	 * R  is the radius of the arc
	 * π  is Pi
	 *
	 * @param angle is the angle the base should be rotated by
	 * @return is the linear distance the wheel needs to travel given the this CHassis's wheel track
	 */
	float chassisRotationToWheelDistance(float angle);
public:
	virtual ~DrivingChassis();

	/**
	 * DrivingChassis encapsulates a 2 wheel differential steered chassis that drives around
	 *
	 * @param left the left motor
	 * @param right the right motor
	 * @param wheelTrackMM is the measurment in milimeters of the distance from the left wheel contact point to the right wheels contact point
	 * @param wheelRadiusMM is the measurment in milimeters of the radius of the wheels
	 */
	DrivingChassis(PIDMotor * left, PIDMotor * right, float wheelTrackMM,
			float wheelRadiusMM);

	/**
	 * Start a drive forward action
	 *
	 * @param mmDistanceFromCurrent is the distance the mobile base should drive forward
	 * @param msDuration is the time in miliseconds that the drive action should take
	 *
	 * @note this function is fast-return and should not block
	 */
	void driveForward(float mmDistanceFromCurrent, int msDuration);
	/**
	 * Start a turn action
	 *
	 * This action rotates the robot around the center line made up by the contact points of the left and right wheels.
	 * Positive angles should rotate to the left
	 *
	 * This rotation is a positive rotation about the Z axis of the robot.
	 *
	 * @param degreesToRotateBase the number of degrees to rotate
	 * @param msDuration is the time in miliseconds that the drive action should take
	 *
	 *  @note this function is fast-return and should not block
	 */
	void turnDegrees(float degreesToRotateBase, int msDuration);
	/**
	 * Check to see if the chassis is performing an action
	 *
	 * @return false is the chassis is driving, true is the chassis msDuration has elapsed
	 *
	 *  @note this function is fast-return and should not block
	 */
	bool isChassisDoneDriving();

};

#endif /* DRIVINGCHASSIS_H_ */
