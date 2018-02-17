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
	positionChooser = new frc::SendableChooser<int>();
	targetChooser = new frc::SendableChooser<int>();
	delayChooser = new frc::SendableChooser<int>();
	driveTrain = chasis;
	gettinPoints = cube;
	scaleColor = '\0'; //Initialized so it wouldn't have a random value on declaration
	switchColor = '\0';

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
	SetupAutoCommands();
	autoTimer.Reset();
	movement = 0;
	autodone = false;
}

void Autonomous::AutoPeriodic()
{

	while (!autodone)
		{
			std::cout << "Command: " << autocommand[position][target][movement].command << std::endl;
			std::cout << "Data: " << autocommand[position][target][movement].data << std::endl;
			std::cout << "Position: " << autocommand[position] << std::endl;
			std::cout << "Target: " << autocommand[position][target] << std::endl << std::endl;

			switch (autocommand[position][target][movement].command)
			{
				case drive:
					if (autoTimer.Get() == 0) {
						driveTrain->ResetHeading();
						timeLimit = autocommand[position][target][movement].data / DRIVE_FT_SEC;
						autoTimer.Start();
					}
					if (autoTimer.Get() < timeLimit) {
						driveTrain->DriveStraight(FORWARD);
					}
					else {
						driveTrain->Stop();
						autoTimer.Reset();
						movement++;
					}
					break;

				case reverse:
					if (autoTimer.Get() == 0) {
						driveTrain->ResetHeading();
						timeLimit = autocommand[position][target][movement].data/DRIVE_FT_SEC;
						autoTimer.Start();
					}
					if (autoTimer.Get() < timeLimit) {
						driveTrain->DriveStraight(REVERSE);
					}
					else {
						driveTrain->Stop();
						autoTimer.Reset();
						movement++;
					}
					break;

				case turn:
					if (autoTimer.Get() == 0) {
						driveTrain->ResetHeading();
						autoTimer.Start();
					}
					if (autoTimer.Get() < TURN_TIMEOUT) {
						driveTrain->DriveTurn(autocommand[position][target][movement].data);
					}
						else {
							driveTrain->Stop();
							autoTimer.Reset();
							movement++;
					}
					break;

				case lift:
					if (autoTimer.Get() == 0) {
						timeLimit = autocommand[position][target][movement].data/LIFT_FT_SEC;
						autoTimer.Start();
					}
					if (autoTimer.Get() < timeLimit) {
						gettinPoints->Lift(CubeDelivery::LiftDirection::Up);
					}
					else {
						gettinPoints->StopLift();
						autoTimer.Reset();
						movement++;
					}
					break;

				case lower:
					if (autoTimer.Get() == 0) {
						timeLimit = autocommand[position][target][movement].data/LIFT_FT_SEC;
						autoTimer.Start();
					}
					if (autoTimer.Get() < timeLimit) {
						gettinPoints->Lift(CubeDelivery::LiftDirection::Down);
					}
					else {
						gettinPoints->StopLift();
						autoTimer.Reset();
						movement++;
					}

					break;

				case push:
					gettinPoints->PushCube();
					autoTimer.Reset();
					movement++;

					break;

				case done:
					autodone = true;
					break;
					}
			}
	}

void Autonomous::AddOptions()
{
	//Function called in constructor to set up dashboard options
	int Center = 0; //3 variables for 3 options from chooser
	int Left = 1;
	int Right = 2;
	positionChooser->AddDefault("Center", Center); //Center will be selected by default
	positionChooser->AddObject("Left", Left); //Other 2 are other options under it
	positionChooser->AddObject("Right", Right);
	frc::SmartDashboard::PutData("Starting Position", positionChooser); //Labels the dropdown box.

	int baseline = 1;
	int exchange = 2; //5 variables for target chooser
	int theSwitch = 3;
	int scale = 4;
	targetChooser->AddDefault("Baseline",baseline); //Default option
	targetChooser->AddObject("Exchange", exchange); //Adds the other 4 target options to the chooser
	targetChooser->AddObject("Switch", theSwitch);
	targetChooser->AddObject("Scale", scale);
	frc::SmartDashboard::PutData("Target", targetChooser); //Labels the dropdown box.

	int No = 0; //Default is no, the 2 options for making the robot wait
	int Yes = 1;
	delayChooser->AddDefault("No", No);
	delayChooser->AddObject("Yes", Yes);
	frc::SmartDashboard::PutData("Delay?", delayChooser); //Labels the dropdown box.
}

//Reads values from the smart dashboard.
void Autonomous::ReadStation()
{
	std::cout << "TChooser: " << targetChooser->GetSelected() << std::endl;
	std::cout << "PChooser: " << positionChooser->GetSelected() << std::endl;

	int targetChoice = targetChooser->GetSelected();
	int positionChoice = positionChooser->GetSelected();

	if(targetChoice == 1)
		target = baseline;
	else if(targetChoice == 2)
		target = exchange;
	else if(targetChoice == 3)
	{
		if(switchColor == 'R')
			target = rightswitch;
		else
			target = leftswitch;
	}
	else if(targetChoice == 4)
	{
		if(switchColor == 'R')
			target = rightscale;
		else
			target = leftscale;
	}

	if(positionChoice == 0)
		position = center;
	else if(positionChoice == 1)
		position = left;
	else if(positionChoice == 2)
		position = right;

	//Decide delay
	if(delayChooser->GetSelected() == 0)
		useDelay = false;
	else
		useDelay = true;
}

void Autonomous::SetupAutoCommands()
{
	std::cout << "SetupAutoCommands()" << std::endl;

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
