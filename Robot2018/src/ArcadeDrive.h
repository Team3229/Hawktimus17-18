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

#ifndef SRC_ARCADEDRIVE_H_
#define SRC_ARCADEDRIVE_H_

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
//#include "WPI_TalonSRX.h"

class ArcadeDrive
{
public:
	ArcadeDrive();
	void ResetHeading(); //Resets the gyro
	void Stop(); //Stops driving the talons.
	void Drive(double& Y, double& X); //Drive the robot forward given the current coordinates from the xbox controller
	void DriveStraight(); //Used for driving the robot straight during autonomous
	void DriveTurn (const int& angle); //Used for driving the robot at an angle during autonomous.

private:
	//Constants for driving
	const float SAFETY_TIMEOUT = 0.01;
	const float MAX_POWER = 0.8;
	const float AUTO_POWER = 0.60;
	const float GYRO_GAIN = 0.259;
	const float COMP_RATION = 0.1111;
	const float TURN_POWER = 0.47;

	//Constants for ports and unique id
	const int GYRO_SPI_PORT = 0;
	const unsigned int LEFT_LEAD_ID = 1;
	const unsigned int RIGHT_LEAD_ID = 2;
	const unsigned int LEFT_FOLLOWER_ID = 3;
	const unsigned int RIGHT_FOLLOWER_ID = 4;

	//TalonSRX's
	static std::shared_ptr<WPI_TalonSRX> leftLead; //Front left, leader
	static std::shared_ptr<WPI_TalonSRX> rightLead; //Front right, leader
	static std::shared_ptr<WPI_TalonSRX> leftFollower; //Back left, follower
	static std::shared_ptr<WPI_TalonSRX> rightFollower; //Back right, follower

	static std::shared_ptr<frc::DifferentialDrive> diffDrive; //Drivetrain

	frc::AnalogGyro gyro { GYRO_SPI_PORT }; //Instantiate gyro and initialize its port
};

#endif /* SRC_ARCADEDRIVE_H_ */
