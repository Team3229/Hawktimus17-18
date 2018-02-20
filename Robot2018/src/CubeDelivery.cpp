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
	bottomSwitch = new frc::DigitalInput(BOTTOMSWITCH_DIO);
	myLift = new frc::Spark(LIFT_PWM);
	myConveyor = new frc::Spark(CONVEYOR_PWM);
}

CubeDelivery::~CubeDelivery()
{
	//Deletes pointers to free up space
	delete bottomSwitch;
	delete myLift;
	delete myConveyor;
}

void CubeDelivery::Conveyor(ConveyorDirection direction)
{
	if (direction == ConveyorDirection::Out) {
		myConveyor->Set(-CONVEYOR_POWER); //Pushes cube out
	}
	else if (direction == ConveyorDirection::In) {
		myConveyor->Set(CONVEYOR_POWER); //Sucks cube in
	}
	std::cout << "Conveyor()" << std::endl;
}

void CubeDelivery::PushCube()
{
	std::cout << "PushCube()" << std::endl;
	myConveyor->Set(CONVEYOR_POWER); //Moves conveyor to push cube out
}

void CubeDelivery::StopConveyor()
{
	//Stops the conveyor when button is not pressed
	myConveyor->StopMotor();
}

void CubeDelivery::Lift(LiftDirection direction)
{
	if (direction == LiftDirection::Up) //&& !topSwitch->Get()) //True = up as long as top switch isn't pressed
	{
		std::cout << "LiftUp()" << std::endl;
		myLift->Set(LIFT_POWER); //Moves lift up
	}
	else if (direction == LiftDirection::Down) //&& !bottomSwitch->Get()) //False = down as long as bottom switch isn't pressed
	{
		std::cout << "LiftDown()" << std::endl;
		myLift->Set(-LIFT_POWER); //Moves lift down
	}
}

void CubeDelivery::StopLift()
{
	//Stops lift when button is not pressed
	myLift->StopMotor();
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

void CubeDelivery::TestLimitSwitch()
{
	using namespace std;
	cout << "TestLimitSwitch()" << endl;

	cout << "Bottom Switch = " << bottomSwitch->Get() << endl; //Outputs the state of the bottom switch
}
