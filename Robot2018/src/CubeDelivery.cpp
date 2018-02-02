/*
 * CubeDelivery.cpp
 *
 *  Created on: Feb 1, 2018
 *      Author: luke
 */

#include <CubeDelivery.h>

CubeDelivery::CubeDelivery()
{
	//Passes in parameters to instantiated objects
	topSwitch = new DigitalInput(TOPSWITCH_DIO);
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

void CubeDelivery::Conveyor(const float conveyorPower)
{
		myLift->Set(conveyorPower); //Go forward
}

void CubeDelivery::StopConveyor()
{
	//Stops the conveyor when button is not pressed
	myConveyor->StopMotor();
}

void CubeDelivery::Lift(const bool &direction)
{
	//Move the lifter
	if ((direction == true) && !topSwitch->Get()) //True = up as long as top switch isn't pressed
	{
		myLift->Set(LIFT_POWER); //Moves lift up
	}
	else if ((direction == false) && !bottomSwitch->Get()) //False = down as long as bottom switch isn't pressed
	{
		myLift->Set(-LIFT_POWER); //Moves lift down
	}
}

void CubeDelivery::StopLift()
{
	//Stops lift when button is not pressed
	myLift->StopMotor();
}
