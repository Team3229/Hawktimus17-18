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
	//Initialize the gyro sensitivity
	gyro.SetSensitivity(GYRO_GAIN);

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

	//Inverts same side motors
	//rightFollower->SetInverted(true);
	//leftFollower->SetInverted(true);

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
	//Apply smoothing curve to acceleration
	Y = (pow(MAX_POWER, Y) * Y);

	//Flip the Y value because of the RobotDrive.Drive function
	//is opposite of the XBoxController
	Y = -Y;

	//Enforce a max power/speed
	if(abs(Y) > MAX_POWER) //If the absolute value of y is greater than the max power we are allowing the Sparks to have (0.8)...
	{
		if (Y < 0) //Test to see if Y is negative (moving forwards, first two quadrants)
		{
			Y = 0 - MAX_POWER; //Make sure y is less than the max power and that it is negative (we are moving forward)
		}
		else //Otherwise we are moving backwards (third and fourth quadrants)
		{
			Y = MAX_POWER; //Make sure that y is less than the max power, postive because we are moving backwards.
		}
	}

	if(abs(X) > MAX_POWER) //Make sure the absolute value of x is not greater than the max power
	{
		if (X < 0) //If we are moving left (second and third quadrants).
		{
			X = 0 - MAX_POWER; //Make sure x is at the max power and that it is negative (we are moving left)
		}
		else //If we are moving right (first and fourth quadrants)
		{
			X = MAX_POWER; //Make sure that x is at the max power and that it is positive (we are moving right)
		}
	}

	std::cout << "diffDrive Y: " << Y << " X: " << X << std::endl; //puts in console our x and y
	diffDrive->ArcadeDrive(Y, X);
}

//Drives Straight only in autonomous
void DriveSystem::DriveStraight()
{
}

//Turns the specified angle (in positive of negative degrees from zero) only in autonomous.
void DriveSystem::DriveTurn (const int& angle)
{
}
