/*
 * File Name:                        CubeDelivery.cpp
 * Author(s):                        Luke Simone
 * Last Modified:                    2/13/2018
 * Team:                             Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the CubeDelivery class which is used to control the lift system which uses
 * limit switches, as well as control the conveyor system. Currently working on lift reset system.
 */

#include "CubeDelivery.h"

CubeDelivery::CubeDelivery()
{
	//Passes in parameters to instantiated objects
	topSwitch = new DigitalInput(TOPSWITCH_DIO); //Might have to use == true/false NEEDS TESTING
	bottomSwitch = new DigitalInput(BOTTOMSWITCH_DIO);
	myLift = new frc::Spark(LIFT_PWM);
	myConveyor = new frc::Spark(CONVEYOR_PWM);
}

CubeDelivery::~CubeDelivery()
{
	//Deletes pointers to free up space
	delete topSwitch;
	delete bottomSwitch;
	delete myLift;
	delete myConveyor;
}

void CubeDelivery::ResetLift()
{
	//Used to reset the lift to its lowest point
	std::cout << "ResetLift()" << std::endl;
	if (!bottomSwitch->Get()) //Moves the lift to its lowest point
	{
		myLift->Set(LIFT_POWER);
	}
	else
	{
		StopLift();
	}
}

void CubeDelivery::Conveyor(double& conveyorPower)
{
	std::cout << "Conveyor()" << std::endl;
	conveyorPower = (pow(MAX_POWER, conveyorPower) * conveyorPower); //Applies smoothing curve to conveyor motor
	myConveyor->Set(-conveyorPower); //Moves conveyor based on conveyorPower
}

void CubeDelivery::StopConveyor()
{
	//Stops the conveyor when button is not pressed
	myConveyor->StopMotor();
}

void CubeDelivery::Lift(const bool direction)
{
	std::cout << "Lift()" << std::endl;
	if ((direction == true) && !topSwitch->Get()) //True = up as long as top switch isn't pressed
	{
		myLift->Set(-LIFT_POWER); //Moves lift up
	}
	else if ((direction == false) && !bottomSwitch->Get()) //False = down as long as bottom switch isn't pressed
	{
		myLift->Set(LIFT_POWER); //Moves lift down
	}
}

void CubeDelivery::StopLift()
{
	//Stops lift when button is not pressed
	myLift->StopMotor();
}

void CubeDelivery::PushCube()
{
	//Reusable function for autonomous to push the cube out off of the conveyor
	static int iterations = 0;

	//Timer portion for pushing the cube out
	if (iterations == 0)
	{
		pushTime.Reset();
		pushTime.Start();
		iterations++;
	}
	else if (pushTime.Get() < PUSH_TIME) //If the timer is less than the push time left
	{
		std::cout << "PushCube()" << std::endl;
		myConveyor->Set(CONVEYOR_POWER); //Moves conveyor to push cube out
	}
	else if (pushTime.Get() > PUSH_TIME) //If the timer is greater than the push time left
	{
		StopConveyor();
		iterations = 0;
	}
}

void CubeDelivery::LiftToScale()
{
	//Reusable function for autonomous to move the lift to the height of the scale
	static int iterations = 0;

	//Gets lift down to the lowest point
	ResetLift();

	//Timer portion of moving the lift to the scale height
	if (iterations == 0)
	{
		scaleTime.Reset();
		scaleTime.Start();
		iterations++;
	}
	else if (scaleTime.Get() < SC_LIFT_TIME) //If the timer is less than scale time left
	{
		std::cout << "LiftToScale()" << std::endl;
		myLift->Set(-LIFT_POWER); //Move lift up
	}
	else if (scaleTime.Get() > SC_LIFT_TIME) //If the timer has passed the scale time left
	{
		StopLift();
		iterations = 0;
	}
}

void CubeDelivery::LiftToSwitch()
{
	//Reusable function for autonomous to move the lift to the height of the switch
	static int iterations = 0;

	//Gets lift down to the lowest point
	ResetLift();

	//Timer portion of moving the lift to the switch height
	if (iterations == 0)
	{
		switchTime.Reset();
		switchTime.Start();
		iterations++;
	}
	else if (switchTime.Get() < SW_LIFT_TIME) //If the timer is less than time switch left
	{
		std::cout << "LiftToSwitch()" << std::endl;
		myLift->Set(-LIFT_POWER); //Move lift up
	}
	else if (scaleTime.Get() > SW_LIFT_TIME) //If timer is greater than switch time left
	{
		StopLift();
		iterations = 0;
	}
}

void CubeDelivery::TestLimitSwitch()
{
	using namespace std;

	cout << "TestLimitSwitch()" << endl;

	cout << "Top Switch = " << topSwitch->Get() << endl; //Outputs to console the state of the top limit switch
	cout << "Bottom Switch = " << bottomSwitch->Get() << endl; //Outputs the state of the bottom switch
}
