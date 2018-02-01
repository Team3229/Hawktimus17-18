#ifndef SRC_ARCADEDRIVE_H_
#define SRC_ARCADEDRIVE_H_

//Standard library includes
#include <iostream>
#include <memory>
#include <string>

//FRC library includes
#include <Timer.h>
#include <GenericHID.h>
#include <math.h>
#include <AnalogGyro.h>
#include <Spark.h>
#include <Drive/DifferentialDrive.h>
#include "ctre/Phoenix.h"

class ArcadeDrive
{
public:
	ArcadeDrive();
	void ResetHeading();
	void Stop();
	void Drive(float Y, float X);
	void DriveStraight();
	void DriveTurn (int angle);

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
