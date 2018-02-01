#include "MiscOps.h"

//Moves the lift system up and down
void MiscOps::MoveLift(int angle)
{
	//Check POV pressed by testing angle
		if(angle == 0)
		{
			lift->Set(LIFT_POWER); //Go up
		}
		else if(angle == 180)
		{
			lift->Set(-LIFT_POWER); //Go down
		}
}

//Stops the lift
void MiscOps::LiftStop()
{
	lift->StopMotor();
}

//Moves the conveyor up or down
void MiscOps::MoveConveyor(bool direction)
{
	if(direction) //If true, move the conveyor forward.
		conveyor->Set(CONVEYOR_FORWARD_POWER);
	else //Otherwise move backwardds
		conveyor->Set(CONVEYOR_BACKWARD_POWER);
}

/*Stops the conveyor*/
void MiscOps::ConveyorStop()
{
	conveyor->StopMotor();
}
