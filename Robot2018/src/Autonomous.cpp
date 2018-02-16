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
	SetupAutoCommands();

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
	autoTimer.Reset();
}

void Autonomous::AutoPeriodic()
{
	while (!autodone)
	{
std::cout << “AutoPeriodic position:” << position << “target:” << target << “movement:” << movement << std::endl;	
		switch (autocommand[position][target][movement].command)
		{
			// Command is drive forward x.x feet
			case drive:
std::cout << “Drive” << “feet:” << autocommand[position][target][movement].data << “timelimit:” << timelimit << “timer:” << movementTimer.Get() << std::endl;	
				if (movementTimer.Get() == 0) {
					chasis->ResetHeading();
					timelimit = autocommand[position][target][movement].data/DRIVE_FT_SEC;
					movementTimer.Start();
				}
				if (movementTimer.Get() < timelimit) {
					chasis->DriveStraight(FORWARD);
				}
				else {
					chasis->Stop();
					movementTimer.Reset();
					movement++;
				}
				break;

			// Command is drive in reverse x.x feet
			case reverse:
std::cout << “Reverse” << “feet:” << autocommand[position][target][movement].data << “timelimit:” << timelimit << “timer:” << movementTimer.Get() << std::endl;	
				if (movementTimer.Get() == 0) {
					chasis->ResetHeading();
					timelimit = autocommand[position][target][movement].data/DRIVE_FT_SEC;
					movementTimer.Start();
				}
				if (movementTimer.Get() < timelimit) {
					chasis->DriveStraight(REVERSE);
				}
				else {
					chasis->Stop();
					movementTimer.Reset();
					movement++;
				}
				break;

			// Command is turn x.x degrees
			case turn:
std::cout << “Turn” << “degrees:” << autocommand[position][target][movement].data << “timelimit:” << timelimit << “timer:” << movementTimer.Get() << std::endl;	
				if (movementTimer.Get() == 0) {
					chasis->ResetHeading();
					time limit = TURN_TIMEOUT;
					movementTimer.Start();
				}
				if (movementTimer.Get() < timelimit) {
					chasis->DriveTurn(autocommand[position][target][movement].data);
				}
				else {
					chasis->Stop();
					movementTimer.Reset();
					movement++;
				}
				break;
			
			// Command is lift x.x feet
			case lift:
std::cout << “Lift” << “feet:” << autocommand[position][target][movement].data << “timelimit:” << timelimit << “timer:” << movementTimer.Get() << std::endl;	
				if (movementTimer.Get() == 0) {
					timelimit = autocommand[position][target][movement].data/LIFT_FT_SEC;
					movementTimer.Start();
				}
				if (movementTimer.Get() < timelimit) {
					CubeDelivery::Lift(UP)();
				}
				else {
					CubeDelivery::Stop();
					movementTimer.Reset();
					movement++;
				}
				break;

			// Command is lower x.x feet
			case lower:
std::cout << “Lower” << “feet:” << autocommand[position][target][movement].data << “timelimit:” << timelimit << “timer:” << movementTimer.Get() << std::endl;	
				if (movementTimer.Get() == 0) {
					timelimit = autocommand[position][target][movement].data/LIFT_FT_SEC;
					movementTimer.Start();
				}
				if (movementTimer.Get() < timelimit) {
					CubeDelivery::Lift(DOWN)();
				}
				else {
					CubeDelivery::Stop();
					movementTimer.Reset();
					movement++;
				}
				break;

			// Command is push cube out
			case push:
std::cout << “Push” << std::endl;	
				CubeDelivery::PushCube();
				movementTimer.Reset();
				movement++;
				break;

			// Command is we are done
			case done:
std::cout << “Done” << std::endl;	
				autodone = true;
				break;
			}
		}
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

	int baseline = 1;
	int exchange = 2; //5 variables for target chooser
	int theswitch = 3;
	int scale = 4;
	targetChooser->AddDefault("Baseline", &baseline); //Default option
	targetChooser->AddObject("Exchange", &exchange); //Adds the other 4 target options to the chooser
	targetChooser->AddObject("Switch", &theswitch);
	targetChooser->AddObject("Scale", &scale);
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

	//Decide target
	switch(*(targetChooser->GetSelected()))
	{
	case 1:
		target = baseline;
		break;
	case 2:
		target = exchange;
		break;
	case 3:
		if (switchColor == ‘R’)
			target = rightswitch;
		else 
			target = leftswitch;
		break;
	case 4:
		if (scaleColor == ‘R’)
			target = rightscale;
		
		else
			target = leftscale;
		break;
	}

	//Decide position of robot
	switch(*(positionChooser->GetSelected()))
	{
	case 0:
		position = center;
		break;
	case 1:
		position = left;
		break;
	case 2:
		position = right;
		break;
	}

	//Decide delay
	if(*(delayChooser->GetSelected()) == 0)
		useDelay = false;
	else
		useDelay = true;
}

//Setup the autonomous command movements
void Autonomous::SetupAutoCommands()
{

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

// start = center, target = left switch
autocommand[center][leftswitch][M1].command = drive;
autocommand[center][leftswitch][M1].data = 8.0;
autocommand[center][leftswitch][M2].command = turn;
autocommand[center][leftswitch][M2].data = -30;
autocommand[center][leftswitch][M3].command = drive;
autocommand[center][leftswitch][M3].data = 1.5;
autocommand[center][leftswitch][M4].command = lift;
autocommand[center][leftswitch][M4].data = 2.0;
autocommand[center][leftswitch][M5].command = push;
autocommand[center][leftswitch][M6].command = lower;
autocommand[center][leftswitch][M6].data = 2.0;
autocommand[center][leftswitch][M7].command = done;

// start = right, target = left switch
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

// start = center, target = right switch
autocommand[center][rightswitch][M1].command = drive;
autocommand[center][rightswitch][M1].data = 8.0;
autocommand[center][rightswitch][M2].command = turn;
autocommand[center][rightswitch][M2].data = 30;
autocommand[center][rightswitch][M3].command = drive;
autocommand[center][rightswitch][M3].data = 1.5;
autocommand[center][rightswitch][M4].command = lift;
autocommand[center][rightswitch][M4].data = 2.0;
autocommand[center][rightswitch][M5].command = push;
autocommand[center][rightswitch][M6].command = lower;
autocommand[center][rightswitch][M6].data = 2.0;
autocommand[center][rightswitch][M7].command = done;

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

// start = left, target = left scale
autocommand[left][leftscale][M1].command = drive;
autocommand[left][leftscale][M1].data = 16.0;
autocommand[left][leftscale][M2].command = turn;
autocommand[left][leftscale][M2].data = 30;
autocommand[left][leftscale][M3].command = drive;
autocommand[left][leftscale][M3].data = 1.5;
autocommand[left][leftscale][M4].command = lift;
autocommand[left][leftscale][M4].data = 6.0;
autocommand[left][leftscale][M5].command = push;
autocommand[left][leftscale][M6].command = lower;
autocommand[left][leftscale][M6].data = 6.0;
autocommand[left][leftscale][M7].command = done;

// start = center, target = left scale
autocommand[center][leftscale][M1].command = drive;
autocommand[center][leftscale][M1].data = 2.0;
autocommand[center][leftscale][M2].command = turn;
autocommand[center][leftscale][M2].data = -90;
autocommand[center][leftscale][M3].command = drive;
autocommand[center][leftscale][M3].data = 4;
autocommand[center][leftscale][M4].command = turn;
autocommand[center][leftscale][M4].data = 90;
autocommand[center][leftscale][M5].command = drive;
autocommand[center][leftscale][M5].data = 12;
autocommand[center][leftscale][M6].command = lift;
autocommand[center][leftscale][M6].data = 6.0;
autocommand[center][leftscale][M7].command = push;
autocommand[center][leftscale][M8].command = lower;
autocommand[center][leftscale][M8].data = 6.0;
autocommand[center][leftscale][M9].command = done;

// start = right, target = left scale
autocommand[right][leftscale][M1].command = drive;
autocommand[right][leftscale][M1].data = 16.0;
autocommand[right][leftscale][M2].command = turn;
autocommand[right][leftscale][M2].data = -90;
autocommand[right][leftscale][M3].command = drive;
autocommand[right][leftscale][M3].data = 8;
autocommand[right][leftscale][M4].command = turn;
autocommand[right][leftscale][M4].data = 90;
autocommand[right][leftscale][M5].command = lift;
autocommand[right][leftscale][M5].data = 6.0;
autocommand[right][leftscale][M6].command = push;
autocommand[right][leftscale][M7].command = lower;
autocommand[right][leftscale][M7].data = 6.0;
autocommand[right][leftscale][M8].command = done;

// start = left, target = right scale
autocommand[left][rightscale][M1].command = drive;
autocommand[left][rightscale][M1].data = 16.0;
autocommand[left][rightscale][M2].command = turn;
autocommand[left][rightscale][M2].data = 90;
autocommand[left][rightscale][M3].command = drive;
autocommand[left][rightscale][M3].data = 8;
autocommand[left][rightscale][M4].command = turn;
autocommand[left][rightscale][M4].data = -90;
autocommand[left][rightscale][M5].command = lift;
autocommand[left][rightscale][M5].data = 6.0;
autocommand[left][rightscale][M6].command = push;
autocommand[left][rightscale][M7].command = lower;
autocommand[left][rightscale][M7].data = 6.0;
autocommand[left][rightscale][M8].command = done;

// start = center, target = right scale
autocommand[center][rightscale][M1].command = drive;
autocommand[center][rightscale][M1].data = 2.0;
autocommand[center][rightscale][M2].command = turn;
autocommand[center][rightscale][M2].data = 90;
autocommand[center][rightscale][M3].command = drive;
autocommand[center][rightscale][M3].data = 4.0;
autocommand[center][rightscale][M4].command = turn;
autocommand[center][rightscale][M4].data = -90;
autocommand[center][rightscale][M5].command = drive;
autocommand[center][rightscale][M5].data = 12.0;
autocommand[center][rightscale][M6].command = lift;
autocommand[center][rightscale][M6].data = 6.0;
autocommand[center][rightscale][M7].command = push;
autocommand[center][rightscale][M8].command = lower;
autocommand[center][rightscale][M8].data = 6.0;
autocommand[center][rightscale][M93].command = done;

// start = right, target = right scale
autocommand[right][rightscale][M1].command = drive;
autocommand[right][rightscale][M1].data = 16.0;
autocommand[right][rightscale][M2].command = turn;
autocommand[right][rightscale][M2].data = -30;
autocommand[right][rightscale][M3].command = drive;
autocommand[right][rightscale][M3].data = 1.5;
autocommand[right][rightscale][M4].command = lift;
autocommand[right][rightscale][M4].data = 6.0;
autocommand[right][rightscale][M5].command = push;
autocommand[right][rightscale][M6].command = lower;
autocommand[right][rightscale][M6].data = 6.0;
autocommand[right][rightscale][M7].command = done;


}