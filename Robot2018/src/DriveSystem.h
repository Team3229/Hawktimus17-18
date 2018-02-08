/*
 * File:			ArcadeDrive.h
 * Author:			Hayden Mann
 * Last Modified:	02/02/18
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
#include <Math.h>

//FRC library includes
#include <Timer.h>
#include <GenericHID.h>
#include <AnalogGyro.h>
#include <Drive/DifferentialDrive.h>
#include "ctre/Phoenix.h"
#include <WPILib.h>

class DriveSystem
{
public:
	DriveSystem();
	~DriveSystem();
	void ResetHeading(); //Resets the gyro
	void Stop(); //Stops driving the talons.
	void Drive(double& Y, double& X); //Drive the robot forward given the current coordinates from the xbox controller
	void DriveStraight(); //Used for driving the robot straight during autonomous
	void DriveTurn (const int& angle); //Used for driving the robot at an angle during autonomous.

private:
	//Constants for driving
	const float SAFETY_TIMEOUT = 0.5;
	const float MAX_POWER = 0.8;
	const float AUTO_POWER = 0.60;
	const float GYRO_GAIN = 0.259;
	const float COMP_RATION = 0.1111;
	const float TURN_POWER = 0.47;

	//Constants for ports and unique id
	const unsigned int GYRO_SPI_PORT = 0;
	const unsigned int LEFT_LEAD_ID = 1;
	const unsigned int RIGHT_LEAD_ID = 2;
	const unsigned int LEFT_FOLLOWER_ID = 3;
	const unsigned int RIGHT_FOLLOWER_ID = 4;

	//TalonSRX's
	WPI_TalonSRX * leftLead; //Front left, leader
	WPI_TalonSRX * rightLead; //Front right, leader
	WPI_TalonSRX * leftFollower; //Back left, follower
	WPI_TalonSRX * rightFollower; //Back right, follower

	DifferentialDrive * diffDrive; //Drivetrain

	frc::AnalogGyro gyro { GYRO_SPI_PORT }; //Instantiate gyro and initialize its port
};

#endif /* SRC_DRIVESYSTEM_H_ */
