/*
 * File:		Autonomous.cpp
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the code to be executed for autonomous mode.
 */

#include "Autonomous.h"

Autonomous::Autonomous()
{
	gyro = new ADXRS450_Gyro(); //Green gyro
	ultra = new AnalogInput(ULTRA_PORT);
	positionChooser = new frc::SendableChooser<int*>();
	targetChooser = new frc::SendableChooser<int*>();
	delayChooser = new frc::SendableChooser<int*>();

	AddOptions();
}

Autonomous::~Autonomous()
{
	delete gyro;
	delete ultra;
	delete positionChooser;
	delete targetChooser;
	delete delayChooser;
}


void Autonomous::AutoInit(std::string colors)
{
	switchColor = colors[0]; //Get the color of the switch

	//ReadStation();
}

void Autonomous::AutoPeriodic(DriveSystem& chasis) { /*Runs either exchange, switch, or baseline based on enums*/}
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
	//Check selection of starting station;
	switch(*(targetChooser->GetSelected()))
	{
	case 0: //User specifies Default
		procedure = Target::D;
		break;

	case 1: //User specifices they want the exchange
		 procedure = Target::E;
		 break;

	case 2:
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
