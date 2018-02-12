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
	gyro.Calibrate();
	gyro.Reset();

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
	gyro.Reset();
}

void DriveSystem::Stop()
{
	diffDrive->ArcadeDrive(0, 0);
	frc::Wait(0.05);
}


void DriveSystem::Drive (double& Y, double& X)
{
	//Flip the Y value because of the RobotDrive.Drive function
	//is opposite of the XBoxController
	Y = -Y;

	std::cout << "diffDrive Y: " << Y << " X: " << X << std::endl; //puts in console our x and y
	diffDrive->ArcadeDrive(Y, X);
}

//Drives Straight only in autonomous
void DriveSystem::DriveStraight(const double time)
{
	static short iterations = 0; //For measuring if this is the first iteration of the method
	double gyroAngle = 0.0; //measures gyro angle to keep the robot straight.

	if(iterations == 0)
	{
		driveTime.Reset(); //Reset and start timer
		driveTime.Start();
		iterations++;
	}
	else if(driveTime.Get() < time) //While the time driven is less than the time needed to go.
	{
		gyroAngle = gyro.GetAngle(); //Find the current angle.

		if(gyroAngle != 0)
		{
			gyroAngle = abs(gyroAngle);
			gyroAngle += -gyroAngle; //Compensate for being either greater than or less than to zero
			diffDrive->ArcadeDrive(AUTO_POWER, gyroAngle); //Drive forward at 0;
		}
		else
		{
			diffDrive->ArcadeDrive(AUTO_POWER, 0); //Angle is already at zero, just move forward.
		}
	}
	else if(driveTime.Get() >= time) //Time is expired
	{
		Stop();
		iterations = 0;
	}
}

//Turns the specified angle (in positive of negative degrees from zero) only in autonomous.
void DriveSystem::DriveTurn (const double& angle)
{
}
