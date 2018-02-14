/*
 * File:		Autonomous.cpp
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the code to be executed for autonomous mode.
 */

#include "Autonomous.h"

Autonomous::Autonomous(DriveSystem * chasis, CubeDelivery * cube)
{
	positionChooser = new frc::SendableChooser<int*>();
	targetChooser = new frc::SendableChooser<int*>();
	delayChooser = new frc::SendableChooser<int*>();
	driveTrain = chasis;
	gettinPoints = cube;
}

Autonomous::~Autonomous()
{
	delete positionChooser;
	delete targetChooser;
	delete delayChooser;
}


void Autonomous::AutoInit(std::string colors)
{
	switchColor = colors[0]; //Get the color of the switch
	scaleColor = colors[1];
}

void Autonomous::AutoPeriodic()
{
	if(turn) //A global variable that signifies if this is first time.
	{
		movementTimer.Reset(); //Reset the timer
		movementTimer.Start();
		turn = false; //Not first time running, dont need to run if again
	}

	if(movementTimer.Get() < 10) //Drive straight while the time is less than the number of seconds needed.
	{
		driveTrain->TestGyro();
		driveTrain->DriveTurn(90);
	}
	else //Time has been reached
	{
		movementTimer.Stop(); //Stop the timer
		turn = true;
	}
}

void Autonomous::Exchange() {}
void Autonomous::Switch () {}
void Autonomous::Baseline() {}


void Autonomous::AddOptions()
{
	//Function called in constructor to set up dashboard options
	int Center = 0; //3 variables for 3 options from chooser
	int Left = 1;
	int Right = 2;
	positionChooser->AddDefault("Center", &Center); //Center will be selected by default
	positionChooser->AddObject("Left", &Left); //Other 2 are other options under it
	positionChooser->AddObject("Right", &Right);
	frc::SmartDashboard::PutData("Starting Position", positionChooser); //Labels the dropdown box.

	int Default = 0; //Default option that will have the robot do NOTHING
	int Exchange = 1; //5 variables for target chooser
	int Switch = 2;
	int Scale = 3;
	int Baseline = 4;
	targetChooser->AddDefault("Default", &Default); //Default option
	targetChooser->AddObject("Exchange", &Exchange); //Adds the other 4 target options to the chooser
	targetChooser->AddObject("Switch", &Switch);
	targetChooser->AddObject("Scale", &Scale);
	targetChooser->AddObject("Baseline", &Baseline);
	frc::SmartDashboard::PutData("Target", targetChooser); //Labels the dropdown box.

	int No = 0; //Default is no, the 2 options for making the robot wait
	int Yes = 1;
	delayChooser->AddDefault("No", &No);
	delayChooser->AddObject("Yes", &Yes);
	frc::SmartDashboard::PutData("Delay?", delayChooser); //Labels the dropdown box.
}

//Reads values from the smart dashboard.
void Autonomous::ReadStation()
{
	/*std::cout << *(targetChooser->GetSelected()) << std::endl;

	//Check selection of starting station;
		switch(*(targetChooser->GetSelected()))
		{
		case 0: //User specifies Default
			procedure = Target::D; //Do nothing for deafult
			break;

		case 1: //User specifices they want the exchange
			 procedure = Target::E;
			 break;

		case 2://runs the switch autos
			switch(*(positionChooser->GetSelected()))
			{
			case 0://center
				//do not go for switch while center
				break;
			case 1://left
				if ( switchColor == 'L')
				{
					driveTrain->DriveStraight(3);
					driveTrain->DriveTurn(90);
					driveTrain->DriveStraight(.5);
					gettinPoints->LiftToSwitch();
					gettinPoints->PushCube();

				}
				else if (switchColor == 'R')
				{
					driveTrain->DriveStraight(3);
					driveTrain->DriveTurn(90);
					driveTrain->DriveStraight(2);
					driveTrain->DriveTurn(90);
					gettinPoints->LiftToSwitch();
					gettinPoints->PushCube();

				}

				break;
			case 2://right
				if (switchColor == 'R')
					{
					driveTrain->DriveStraight(3);
					driveTrain->DriveTurn(-90);
					driveTrain->DriveStraight(.5);
					gettinPoints->LiftToSwitch();
					gettinPoints->PushCube();

					}
					else if (switchColor == 'L')
					{
					driveTrain->DriveStraight(3);
					driveTrain->DriveTurn(-90);
					driveTrain->DriveStraight(2);
					driveTrain->DriveTurn(-90);
					gettinPoints->LiftToSwitch();
					gettinPoints->PushCube();
					}
				break;
			}
			procedure = Target::SW;
			break;

		case 3:
			procedure = Target::SC;
			switch(*(positionChooser->GetSelected()))
			{
			case 0://center
				//do not go for scale while center
				break;
			case 1://left
				if ( scaleColor == 'L')
				{
					driveTrain->DriveStraight(6);
					driveTrain->DriveTurn(90);
					gettinPoints->LiftToScale();
					gettinPoints->PushCube();

				}
				else if (scaleColor == 'R')
				{
					driveTrain->DriveStraight(5);
					driveTrain->DriveTurn(90);
					driveTrain->DriveStraight(3);
					driveTrain->DriveTurn(-90);
					driveTrain->DriveStraight(75);
					driveTrain->DriveTurn(-90);
					gettinPoints->LiftToScale();
					gettinPoints->PushCube();

				}

				break;
			case 2://right
				if (scaleColor == 'R')
					{
					driveTrain->DriveStraight(6);
					driveTrain->DriveTurn(-90);
					gettinPoints->LiftToScale();
					gettinPoints->PushCube();

					}
					else if (scaleColor == 'L')
					{
						driveTrain->DriveStraight(5);
						driveTrain->DriveTurn(-90);
						driveTrain->DriveStraight(3);
						driveTrain->DriveTurn(90);
						driveTrain->DriveStraight(.75);
						driveTrain->DriveTurn(90);
						gettinPoints->LiftToScale();
						gettinPoints->PushCube();

					}
				break;
			}
			break;

		case 4:
			procedure = Target::B;
			driveTrain->DriveStraight(5);
			break;
		}*/
	}

//Drives the robot straight for a given number of seconds
void Autonomous::DriveStraight(int seconds)
{
	if(turn) //A global variable that signifies if this is first time.
	{
		movementTimer.Reset(); //Reset the timer
		movementTimer.Start();
		turn = false; //Not first time running, dont need to run if again
	}

	if(movementTimer.Get() < seconds) //Drive straight while the time is less than the number of seconds needed.
	{
		driveTrain->DriveStraight();
	}
	else //Time has been reached
	{
		driveTrain->Stop(); //Stop driving
		movementTimer.Stop(); //Stop the timer
		turn = true; //Run top if again.
	}
}
