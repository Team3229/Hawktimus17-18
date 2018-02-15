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
	scaleColor = colors[1]; //get the4 color of the scale
	ReadStation();

		if (autotarget == baseline)
		{
			target = baseline;
		}
		else if (autotarget == exchange)
		{
			target = exchange;
		}
		else if (autotarget == switch)
		{
			if (switchColor == L)
			{
				target = leftswitch;
			}
			else
			{
				target = rightswitch;
			}
		}
		else if (autotarget == scale)
		{
			if (scaleColor == L)
			{
				target = leftscale;
			}
			else
			{
				target = rightswitch;
			}
		}

autoTimer.Reset();

// start = left, target = baseline
autocommand[left][baseline][M1].command = drive;
autocommand[left][baseline][M1].data = 8.0;
autocommand[left][baseline][M2].command = done;

// start = center, target = baseline
autocommand[center][baseline][M1].command = drive;
autocommand[center][baseline][M1].data = 8.0;
autocommand[center][baseline][M2].command = done;

// start = right, target = baseline
autocommand[right][baseline][M1].command = drive;
autocommand[right][baseline][M1].data = 8.0;
autocommand[right][baseline][M2].command = done;

// start = left, target = exchange
autocommand[left][exchange][M1].command = drive;
autocommand[left][exchange][M1].data = 8.0;
autocommand[left][exchange][M2].command = reverse;
autocommand[left][exchange][M2].data = 5.0;
autocommand[left][exchange][M3].command = turn;
autocommand[left][exchange][M3].data = 90;
autocommand[left][exchange][M4].command = drive;
autocommand[left][exchange][M4].data = 3.0;
autocommand[left][exchange][M5].command = turn;
autocommand[left][exchange][M5].data = 90;
autocommand[left][exchange][M6].command = drive;
autocommand[left][exchange][M6].data = 3.0;
autocommand[left][exchange][M7].command = push;
autocommand[left][exchange][M8].command = done;

//start = center, target = exchange
autocommand[center][exchange][M1].command = drive;
autocommand[center][exchange][M1].data = 8.0;
autocommand[center][exchange][M2].command = reverse;
autocommand[center][exchange][M2].data = 5.0;
autocommand[center][exchange][M3].command = turn;
autocommand[center][exchange][M3].data = -90;
autocommand[center][exchange][M4].command = drive;
autocommand[center][exchange][M4].data = 3.0;
autocommand[center][exchange][M5].command = turn;
autocommand[center][exchange][M5].data = -90;
autocommand[center][exchange][M6].command = drive;
autocommand[center][exchange][M6].data = 3.0;
autocommand[center][exchange][M7].command = push;
autocommand[center][exchange][M8].command = done;

//start = right, target = exchange
autocommand[right][exchange][M1].command = drive;
autocommand[right][exchange][M1].data = 8.0;
autocommand[right][exchange][M2].command = reverse;
autocommand[right][exchange][M2].data = 5.0;
autocommand[right][exchange][M3].command = turn;
autocommand[right][exchange][M3].data = -90;
autocommand[right][exchange][M4].command = drive;
autocommand[right][exchange][M4].data = 8.0;
autocommand[right][exchange][M5].command = turn;
autocommand[right][exchange][M5].data = -90;
autocommand[right][exchange][M6].command = drive;
autocommand[right][exchange][M6].data = 3.0;
autocommand[right][exchange][M7].command = push;
autocommand[right][exchange][M8].command = done;

// start = left, target = left switch
autocommand[left][leftswitch][M1].command = drive;
autocommand[left][leftswitch][M1].data = 8.0;
autocommand[left][leftswitch][M2].command = turn;
autocommand[left][leftswitch][M2].data = 30;
autocommand[left][leftswitch][M3].command = drive;
autocommand[left][leftswitch][M3].data = 1.5;
autocommand[left][leftswitch][M4].command = lift;
autocommand[left][leftswitch][M4].data = 2.0;
autocommand[left][leftswitch][M5].command = push;
autocommand[left][leftswitch][M6].command = lower;
autocommand[left][leftswitch][M6].data = 2.0;
autocommand[left][leftswitch][M7].command = done;

// start = left, target = right switch
autocommand[left][rightswitch][M1].command = drive;
autocommand[left][rightswitch][M1].data = 10.0;
autocommand[left][rightswitch][M2].command = turn;
autocommand[left][rightswitch][M2].data = 90;
autocommand[left][rightswitch][M3].command = drive;
autocommand[left][rightswitch][M3].data = 4;
autocommand[left][rightswitch][M4].command = turn;
autocommand[left][rightswitch][M4].data = 90;
autocommand[left][rightswitch][M5].command = lift;
autocommand[left][rightswitch][M5].data = 2.0;
autocommand[left][rightswitch][M6].command = push;
autocommand[left][rightswitch][M7].command = lower;
autocommand[left][rightswitch][M7].data = 2.0;
autocommand[left][rightswitch][M8].command = done;

// start = right, target = right switch
autocommand[right][rightswitch][M1].command = drive;
autocommand[right][rightswitch][M1].data = 8.0;
autocommand[right][rightswitch][M2].command = turn;
autocommand[right][rightswitch][M2].data = -30;
autocommand[right][rightswitch][M3].command = drive;
autocommand[right][rightswitch][M3].data = 1.5;
autocommand[right][rightswitch][M4].command = lift;
autocommand[right][rightswitch][M4].data = 2.0;
autocommand[right][rightswitch][M5].command = push;
autocommand[right][rightswitch][M6].command = lower;
autocommand[right][rightswitch][M6].data = 2.0;
autocommand[right][rightswitch][M7].command = done;

// start = right, target = right switch
autocommand[right][leftswitch][M1].command = drive;
autocommand[right][leftswitch][M1].data = 10.0;
autocommand[right][leftswitch][M2].command = turn;
autocommand[right][leftswitch][M2].data = -90;
autocommand[right][leftswitch][M3].command = drive;
autocommand[right][leftswitch][M3].data = 4;
autocommand[right][leftswitch][M4].command = turn;
autocommand[right][leftswitch][M4].data = -90;
autocommand[right][leftswitch][M5].command = lift;
autocommand[right][leftswitch][M5].data = 2.0;
autocommand[right][leftswitch][M6].command = push;
autocommand[right][leftswitch][M7].command = lower;
autocommand[right][leftswitch][M7].data = 2.0;
autocommand[right][leftswitch][M8].command = done;
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
std::cout << *(targetChooser->GetSelected()) << std::endl;

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

			procedure = Target::SW;
			break;

		case 3:
			procedure = Target::SC;

			break;

		case 4:
			procedure = Target::B;

			break;
		}
	}
}
