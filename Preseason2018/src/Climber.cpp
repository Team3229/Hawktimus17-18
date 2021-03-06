/*
 * File:		Climber.cpp
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Controls the climber.
 */

#include "Climber.h"

Climber::Climber()
{
	myClimber = new frc::Spark(CLIMBER_PWM);
}

void Climber::Stop()
{
	myClimber->StopMotor();
}

void Climber::Climb()
{
	debug("Climb()" << std::endl);
	myClimber->Set(CLIMBER_POWER);
}
