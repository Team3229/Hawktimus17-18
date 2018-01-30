/*
 * File:			Autonomous.cpp
 * Author:			Neil Anderson
 * Version:			1.0
 * Last Modified:	01/16/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * This file defines all methods of the autonomous class, which defines all methods that drive the robot while in autonomous mode.
 */

#include <Autonomous.h>

// 4 choosers to determine what the robot will do
frc::SendableChooser<int *> autoChooser; //An object of the SendableChooser class, which allows the programmer to add options to the "Select Autonomous..." menu on the SmartDashboard
frc::SendableChooser<int *> crossOverChooser; //An object of the SendableChooser class, which allows the programmer to add options to the "Select Autonomous..." menu on the SmartDashboard
frc::SendableChooser<int *> targetChooser; //An object of the SendableChooser class, which allows the programmer to add options to the "Select Autonomous..." menu on the SmartDashboard
frc::SendableChooser<int *> waitChooser; //An object of the SendableChooser class, which allows the programmer to add options to the "Select Autonomous..." menu on the SmartDashboard

///four constant strings which define the options presented to the user for selecting the autonomouse mode.
const std::string autoDefault = "Default";
const std::string autoCenter = "Center";
const std::string autoRight = "Right";
const std::string autoLeft = "Left";

// Second set of options for crossing over or not
// Should probably be reworked with a boolean
const std::string crossOverNo = "No";
const std::string crossOverYes = "Yes";

// Wait for x amount of seconds before starting auto
// Shoud probably be reworked with a boolean
const std::string waitGo = "Go";
const std::string waitWait = "Wait";

// Last set of options
const std::string targetSwitch = "Switch";
const std::string targetScale = "Scale";
const std::string targetBaseline = "Baseline";

//Three integers defining the order in which the options appear on the SmartDashboard, respectively.
int Default = 0;
int Center = 1;
int Right = 2;
int Left = 3;

int *autoSelected = &Default; //Will hold the option the user selected from the dashboard.

enum positions {D, C, R, L}; //An enumeration that will aid in deciding which autonomous mode the user selected, by only allowing for three possibilities.
positions position = D; //A variable of that enumeration that is initialized to C by default.

//BASICALLY A DYNAMIC VERSION OF VISUAL BASIC
void Autonomous::AutoSelectInit() //A method that adds certain autonomous mode options to the SmartDashboard
{
	//Display the Autonomous Selection Options on Driver Station
	autoChooser.AddDefault(autoDefault, &Default); //Adds the default option
	autoChooser.AddObject(autoCenter, &Center); //Adds the center option
	autoChooser.AddObject(autoLeft, &Left); //Adds the left option
	autoChooser.AddObject(autoRight, &Right); //Adds the right option
	frc::SmartDashboard::PutData("Auto Mode", &autoChooser); //Labels the dropdown box.
}

int No = 0;
int Yes = 1;

int *crossOverSelected = &No; // Holds the crossing over option from dashboard

enum crossingOver {Y, N}; //Enumberation for crossing over selection
crossingOver crossingOver = N; //Default option

void Autonomous::CrossOverSelectInit() // Method to ask the driver if they wish to cross over or not
{
	//Displays yes or no for crossing over
	crossOverChooser.AddDefault(crossOverNo, &No); // Default option is no
	crossOverChooser.AddObject(crossOverYes, &Yes); // Adds yes option
	frc::SmartDashboard::PutData("Crossing Over?", &crossOverChooser); //Labels the dropdown box.
}

int Switch = 0;
int Scale = 1;
int Baseline = 2;

int *targetSelected = &Switch; // Holds the target option from the dashboard

enum target {SW, SC, BL}; // Enumerations for target options
target target = SW; // Default option is switch

void Autonomous::TargetSelectInit()
{
	//Displays the 3 target options
	targetChooser.AddDefault(targetSwitch, &Switch);
	targetChooser.AddObject(targetScale, &Scale);
	targetChooser.AddObject(targetBaseline, &Baseline);
	frc::SmartDashboard::PutData("Target", &targetChooser); // Lables target box
}

int Go = 0;
int Wait = 1;

int *waitSelected = &Go;

void Autonomous::WaitSelectInit()
{
	// Displays 2 options, to wait or not to wait
	waitChooser.AddDefault(waitGo, &Go);
	waitChooser.AddObject(waitWait, &Wait);
	frc::SmartDashboard::PutData("Wait?", &waitChooser); // Labels to wait or not chooser
}

//VARIABLES FOR AUTONOMOUS PERIODIC EXECUTION
enum autoStates {M1, M2, M3, M4, M5}; //An enumeration that defines the movement the robot is currently doing.
autoStates autoState = M1; //Initialized a variable of this enumeration
Timer moveTimer; //A timer object used for timing the movements of the robot.
int turn_angle;  //Will hold the direction angle that the robot needs to turn.  Will be passed to the gyro object.
bool autoDone = false; //Will hold if the current process is finished or not.

Autonomous::Autonomous() {} //Default Constructor

//BASICALLY A DYNAMIC VERSION OF VISUAL BASIC
void Autonomous::AutoSelectInit() //A method that adds certain autonomous mode options to the SmartDashboard
{
	//Display the Autonomous Selection Options on Driver Station
	autoChooser.AddDefault(autoCenter, &Center); //Adds the center option
	autoChooser.AddObject(autoLeft, &Left); //Adds the left option
	autoChooser.AddObject(autoRight, &Right); //Adds the right option
	frc::SmartDashboard::PutData("Auto Mode", &autoChooser); //Labels the dropdown box.
}

void Autonomous::DoAutonomousInit()
{
	//Get the Autonomous Selection from the Driver Station
	autoSelected = autoChooser.GetSelected(); //Set autoSelected (a pointer) to whatever the user selects from the dropdown menu.
	std::cout << "Auto Selected: " << autoSelected << std::endl; //Output to the console what the user selected for autonomous.

	//Decide what to do based on the user's selection (autoSelected is a pointer, hence the use of the & operator).
	if (autoSelected == &Center)
	{
		position = C; //Set position equal to C (enum) if the user selects "center".
	}
	else if(autoSelected == &Right)
	{
		position = R; //Set position equal to R (enum) if the user selects "right".
		turn_angle = LEFT_TURN; //Set the turn angle equal to -30 degrees.
	}
	else if (autoSelected == &Left)
	{
		position = L; //Set position equal to L (enum) if the user selects "left".
		turn_angle = RIGHT_TURN; //Set the turn angle equal to 30 degrees.
	}

	moveTimer.Reset(); //Zero-out the timer
	autoDone = false; //Set to false (auto is not done)
	autoState = M1; //We need to do Movement 1 first, so make sure that what we're gonna do first.
}

//Controls the movements of the robot during autonomous and implements methods of the ArcadeDrive class in order for the RoboRIO to send signals to the sparc controllers.
void Autonomous::DoAutonomousPeriodic(ArcadeDrive * chasis)
{
	//While autonomous movements are not done (because it is re-entrant)
	if(! autoDone)
	{
		switch(position) //Based on the already defined position of the robot, decide which action to take.
		{
		case C: //If the robot is in the center...
			if(moveTimer.Get() == 0) //Find out if the timer is at 0 or not. If it is, prepare the robot to start moving.
			{
				chasis->ResetHeading(); //Reset the gyro so that it can figure out where 0 is.
				moveTimer.Start();
			}

			if(moveTimer.Get() < CENTER_TIMER) //Subsequent Times
			{
				chasis->DriveStraight(); //Drive straight for four seconds (less than CENTER_TIMER).
			}
			else //We are done
			{
				chasis->Stop();
				moveTimer.Reset();
				autoDone = true;
			}
			break;

		//Right or Left position - drive, turn, drive to peg
		case R:
		case L:
			switch (autoState)//Begin to track movements (M1, M2, M3)
			{
			//Movement 1 - drive straight for x.x seconds
			case M1:
				if(moveTimer.Get() == 0) //First Time
				{
					chasis->ResetHeading(); //Reset the gyro
					moveTimer.Start(); //Start the timer
				}
				if(moveTimer.Get() < MOVEMENT1_TIMER) //Subsequent times
				{
					chasis->DriveStraight();
				}
				else //we are done with this movement
				{
					chasis->Stop();
					chasis->ResetHeading();
					moveTimer.Reset();
					autoState = M2; //Move to the next movement.  Will run a different case because program is re-entrant
				}
				break;

			//Movement 2 - turn left or right
			case M2:
				chasis->DriveTurn(turn_angle); //Turn left
				chasis->Stop();
				moveTimer.Reset();
				autoState = M3;
				break;

			//Movement 3 - drive straight x.x seconds
			case M3:
				if(moveTimer.Get() == 0) //first time
				{
					chasis->ResetHeading(); //Reset the gyro
					moveTimer.Start();
				}
				if(moveTimer.Get() < MOVEMENT3_TIMER) //Subsequent times
				{
					chasis->DriveStraight(); //Drive forward (this method is only used in autonomous).
				}
				else
				{
					chasis->Stop(); //We are done
					moveTimer.Reset();
					autoDone = true;
				}
			}
		}
	}
}
