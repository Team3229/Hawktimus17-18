/*
 * File:			ArcadeDrive.h
 * Author:			Hayden Mann
 * Last Modified:	02/02/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Defines the prototypes of the ArcadeDrive class defined in ArcadeDrive.h.  The ArcadeDrive class contains
 * signatures for all methods and instance variables necessary for driving the robot in either
 * TeleOp or Autonomous modes, using arcade drive and TalonSRX's.
 */

#include <ArcadeDrive.h>

ArcadeDrive::ArcadeDrive()
{
	using namespace std;

	//Initialize the gyro sensitivity
	gyro.SetSensitivity(GYRO_GAIN);

	//Instantiate motors.
	leftLead.reset(new WPI_TalonSRX(LEFT_LEAD_ID));
	rightLead.reset(new WPI_TalonSRX(RIGHT_LEAD_ID));
	leftFollower.reset(new WPI_TalonSRX(LEFT_FOLLOWER_ID));
	rightFollower.reset(new WPI_TalonSRX(RIGHT_FOLLOWER_ID));

	//Instantiate DriveTrain
	diffDrive.reset(new frc::DifferentialDrive(*leftLead, *rightLead));

	//Implement drive train safety
	diffDrive->SetExpiration(SAFETY_TIMEOUT); //Set safety
	diffDrive->SetMaxOutput(0.8);

	//Set followers
	leftFollower->Set(ControlMode::Follower, LEFT_LEAD_ID); //L2 follows L1
	rightFollower->Set(ControlMode::Follower, RIGHT_LEAD_ID); //R2 follows R1
}

void ArcadeDrive::ResetHeading()
{
	//Reset the gyro so zero angle is straight ahead
	gyro.Reset();
}

void ArcadeDrive::Stop()
{
	diffDrive->ArcadeDrive(0, 0);
	Wait(0.05);
}


void ArcadeDrive::Drive (double& Y, double& X)
{
	//Apply smothing curve to acceleration
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

	diffDrive->ArcadeDrive(-Y, X);
}

//Drives Straight only in autonomous
void ArcadeDrive::DriveStraight()
{
}

//Turns the specified angle (in positive of negative degrees from zero) only in autonomous.
void ArcadeDrive::DriveTurn (const int& angle)
{
}
