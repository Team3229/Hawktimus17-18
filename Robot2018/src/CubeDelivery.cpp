/*
 * CubeDelivery.cpp
 *
 *  Created on: Feb 1, 2018
 *      Author: luke
 */

#include <CubeDelivery.h>

CubeDelivery::CubeDelivery()
{
	topSwitch = new DigitalInput();
	bottomSwitch = new DigitalInput();
	myLift = new frc::Spark(LIFT_PWM);
	myConveyor = new frc::Spark(CONVEYOR_PWM);

}
