/*
 * File Name:                        CubeDelivery.cpp
 * Author(s):                        Luke Simone
 * Last Modified:                    2/2/2018
 * Team:                             Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the CubeDelivery class which is used to control the lift system which uses
 * limit switches, as well as control the conveyor system.
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

void CubeDelivery::Conveyor(double &conveyorPower)
{
	conveyorPower = (pow(MAX_POWER, conveyorPower) * conveyorPower); //Applies smoothing curve to conveyor motor
	myLift->Set(-conveyorPower); //Moves conveyor based on conveyorPower
}

void CubeDelivery::StopConveyor()
{
	//Stops the conveyor when button is not pressed
	myConveyor->StopMotor();
}

void CubeDelivery::Lift(const bool direction)
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
