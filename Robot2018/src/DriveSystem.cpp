/*
 * File:			ArcadeDrive.cpp
 * Author:			Hayden Mann
 * Last Modified:	02/03/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the code for arcade drive and talons.
 *
 * Connect to robot: roborio-3229-FRC.local
 */

#include "DriveSystem.h"

DriveSystem::DriveSystem()
{
	//Initialize the gyro and reset to zero
	gyro = new ADXRS450_Gyro{frc::SPI::kOnboardCS0};
	gyro->Calibrate();
	gyro->Reset();

	//Instantiate motor controllers
	leftLead = new WPI_TalonSRX(LEFT_LEAD_ID);
	rightLead = new WPI_TalonSRX(RIGHT_LEAD_ID);
	leftFollower = new WPI_TalonSRX(LEFT_FOLLOWER_ID);
	rightFollower = new WPI_TalonSRX(RIGHT_FOLLOWER_ID);

	//Reset the controllers
	leftLead->Set(ControlMode::PercentOutput, 0);
	rightLead->Set(ControlMode::PercentOutput, 0);
	leftFollower->Set(ControlMode::PercentOutput, 0);
	leftFollower->Set(ControlMode::PercentOutput, 0);

	//Sets smoothing curve to talons
	leftLead->ConfigOpenloopRamp(SMOOTH_TIME, 0); //passes in seconds from neutral to full and timeout in miliseconds
	rightLead->ConfigOpenloopRamp(SMOOTH_TIME, 0);
	leftFollower->ConfigOpenloopRamp(SMOOTH_TIME, 0);
	rightFollower->ConfigOpenloopRamp(SMOOTH_TIME, 0);

	//Clears sticky faults
	leftLead->ClearStickyFaults(0);
	rightLead->ClearStickyFaults(0);
	leftFollower->ClearStickyFaults(0);
	rightFollower->ClearStickyFaults(0);

	//Set followers
	leftFollower->Follow(*leftLead);
	rightFollower->Follow(*rightLead);

	//Instantiate DriveTrain
	diffDrive = new frc::DifferentialDrive(*leftLead, *rightLead);

	//Implement drive train safety
	diffDrive->SetExpiration(SAFETY_TIMEOUT); //Set safety
	diffDrive->SetMaxOutput(MAX_OUTPUT);

}

DriveSystem::~DriveSystem()
{
	delete leftLead;
	delete rightLead;
	delete leftFollower;
	delete rightFollower;
	delete diffDrive;
}

void DriveSystem::ResetHeading()
{
	//Reset the gyro so zero angle is straight ahead
	gyro->Reset();
}

void DriveSystem::Stop()
{
	diffDrive->ArcadeDrive(0, 0);
}


void DriveSystem::Drive (double& Y, double& X)
{
	//Flip the Y value because of the RobotDrive.Drive function
	//is opposite of the XBoxController
	Y = -Y;

	std::cout << "diffDrive Y: " << Y << " X: " << X << std::endl; //puts in console our x and y
	diffDrive->ArcadeDrive(Y, X);
}

void DriveSystem::DriveStraight()
{
	diffDrive->ArcadeDrive(AUTO_POWER, 0.0); //Drives the robot straight
}

//Turns the specified angle (in positive of negative degrees from zero) only in autonomous.
void DriveSystem::DriveTurn (double angle)
{
	double gyroAngle = 0.0;

	if(angle > 180)
		angle = angle - 360;

	if(turn)
	{
		gyro->Reset(); //For if a turn is made.
		turn = false;
	}

	gyroAngle = gyro->GetAngle();

	if(gyroAngle < angle)
	{
		if(angle < 0)
		{
			diffDrive->ArcadeDrive(AUTO_POWER, -1.0);
		}
		else
		{
			diffDrive->ArcadeDrive(AUTO_POWER, 1.0);
		}
	}
	else
	{
		Stop();
		turn = true;
		Wait(2.0);
	}
}

void DriveSystem::TestGyro()
{
	//gyro.Reset();
	//gyro.SetSensitivity(0.259);

	double angle = gyro->GetAngle();
	std::cout << "Gyro angle: " << angle << std::endl;
}
