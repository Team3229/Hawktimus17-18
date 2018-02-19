/*
 * File:			ArcadeDrive.h
 * Author:			Hayden Mann
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Defines the class and necessary includes for the ArcadeDrive.cpp file.  The ArcadeDrive class defines
 * all methods and instance variables necessary for driving the robot in either TeleOp or Autonomous modes,
 * using arcade drive.
 */

#ifndef SRC_DRIVESYSTEM_H_
#define SRC_DRIVESYSTEM_H_

//Standard library includes
#include <iostream>
#include <memory>
#include <string>

//FRC library includes
#include <Timer.h>
#include <GenericHID.h>
#include <ADXRS450_Gyro.h>
#include <Drive/DifferentialDrive.h>
#include "ctre/Phoenix.h"

class DriveSystem
{
public:
	DriveSystem();
	~DriveSystem();
	void ResetHeading(); //Resets the gyro
	void Stop(); //Stops driving the talons.
	void Drive(double& Y, double& X); //Drive the robot forward given the current coordinates from the xbox controller
	void DriveStraight(bool direction); //Used for driving the robot straight during autonomous
	void DriveTurn (double angle); //Used for driving the robot at an angle during autonomous.
	void TestGyro();
	void ChangeSpeed(bool speed); //Used to change the robot speed during TeleOp

	const float SMOOTH_TIME = .5; //Sets time in seconds the motors take to get from neutral to full power

private:
	//TalonSRX's
	WPI_TalonSRX * leftLead; //Front left, leader
	WPI_TalonSRX * rightLead; //Front right, leader
	WPI_TalonSRX * leftFollower; //Back left, follower
	WPI_TalonSRX * rightFollower; //Back right, follower

	DifferentialDrive * diffDrive; //Drivetrain
	ADXRS450_Gyro * gyro; //Instantiate gyro and initialize its port
	frc::Timer driveTime{};

	//Constants for ports and unique id
	const unsigned int LEFT_LEAD_ID = 1;
	const unsigned int LEFT_FOLLOWER_ID = 2;
	const unsigned int RIGHT_LEAD_ID = 3;
	const unsigned int RIGHT_FOLLOWER_ID = 4;

	//Constants for driving
	const float SAFETY_TIMEOUT = 0.5;
	const float MAX_OUTPUT = 0.6;
	const float LOW_OUTPUT = 0.3; //Lower output for TeleOp
	const float AUTO_POWER = 0.9;
	const float TURN_POWER_Y = 0.47;
	const float TURN_POWER_X = 0.47; //Was 1.0
	const float STRAIGHT_ADJUST = 0.1;
};

#endif /* SRC_DRIVESYSTEM_H_ */
