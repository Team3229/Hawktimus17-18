/*
 * File:			Robot.cpp
 * Author(s):		Hayden Mann
 * Last Modified:	02/02/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the default class for running the robot through the roboRIO for the 2018 build season
 *
 * Connect to robot: roborio-3229-FRC.local
 */

#include "Robot.h"

//Runs once on first boot of Robot
void Robot::RobotInit()
{
	debug("RobotInit()" << std::endl);
	autoMode.AddOptions();
	autoMode.SetupAutoCommands();
}

//Runs once when Autonomous starts
void Robot::AutonomousInit()
{
	debug("AutonomousInit()" << std::endl);
	chasis.ChangeSpeed(DriveSystem::MotorSpeed::Normal);
	//Get the Autonomous Selection from the Driver Station, pass in Game string for random colors.
	autoMode.AutoInit(frc::DriverStation::GetInstance().GetGameSpecificMessage());
}

//Runs continually during Autonomous
void Robot::AutonomousPeriodic()
{
	debug("AutonomousPeriodic()" << std::endl);
	if (!autoMode.autodone)
	{
		autoMode.AutoPeriodic();
	}
	//While autonomous movements are not done (because it is re-entrant)
}

//Runs once Teleop starts
void Robot::TeleopInit()
{
	autoMode.autodone = true;
	debug("TeleopInit()" << std::endl);
	chasis.ChangeSpeed(DriveSystem::MotorSpeed::Normal);
}

//Runs continually during Teleop
void Robot::TeleopPeriodic()
{
	double leftY, leftX, rightY; //An x and y coordinate.
	debug("TeleopPeriodic()" << std::endl);

	//Drive (left hand joystick on the controller)
	//Get both the x and y coordinates from the left joystick.
	leftY = xbox.GetY(GenericHID::kLeftHand);
	leftX = xbox.GetX(GenericHID::kLeftHand);
	if(abs(leftX) > DEAD_BAND_LEFT || abs(leftY) > DEAD_BAND_LEFT)
	{
		chasis.Drive(leftY, leftX);
	}
	else
	{
		chasis.Stop();
	}

	//Climber (right hand "Y" button)
	if (xbox.GetYButton()) //Map the right hand "bumper" (trigger) button to the climber PWM, button is pressed.
	{
		climberMotor.Climb(); //Climbs
	}
	else
	{
		climberMotor.Stop(); //button released
	}

	//Map right joystick for the conveyor
	rightY = xbox.GetRawAxis(5);
	if (abs(rightY) > DEAD_BAND_RIGHT)
	{
		if (rightY < DEAD_BAND_RIGHT)
		{
			gettinPoints.Lift(CubeDelivery::LiftDirection::Up); //Move the lift system up
		}
		else
		{
			gettinPoints.Lift(CubeDelivery::LiftDirection::Down); //Move the lift system down
		}
	}
	else
	{
		gettinPoints.StopLift();
	}


	//Map the left and right bumper to the climbers
	if(xbox.GetBumper(GenericHID::kRightHand)) //Right bumper
	{
		gettinPoints.Conveyor(CubeDelivery::ConveyorDirection::Out); //Push cube out
	}
	else if(xbox.GetBumper(GenericHID::kLeftHand)) //Left bumper
	{
		gettinPoints.Conveyor(CubeDelivery::ConveyorDirection::In); //Succ cube in
	}
	else
	{
		gettinPoints.StopConveyor();
	}

	//2 buttons to switch between high and low power
	if (xbox.GetAButton()) //A button
	{
		//Sets normal speed
		chasis.ChangeSpeed(DriveSystem::MotorSpeed::Normal);
	}
	if (xbox.GetBButton()) //B button
	{
		//Sets the lower power mode
		chasis.ChangeSpeed(DriveSystem::MotorSpeed::Low);
	}
	if (xbox.GetXButton()) //X button
	{
		//Sets high power mode
		chasis.ChangeSpeed(DriveSystem::MotorSpeed::High);
	}
	Wait(0.05);
}
	//Test mode
void Robot::TestPeriodic()
{
	debug("TestPeriodic()" << std::endl);
}

START_ROBOT_CLASS(Robot);
