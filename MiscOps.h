/*
 * MiscOps.h
 *
 *  Created on: Jan 31, 2018
 *      Author: HaydenJ
 */

#ifndef SRC_MISCOPS_H_
#define SRC_MISCOPS_H_

#include <iostream>
#include <string>

#include <Spark.h>

#define LIFT_PWM 0
#define CONVEYOR_PWM 1
#define LIFT_POWER 0.8
#define CONVEYOR_FORWARD_POWER 0.5
#define CONVEYOR_BACKWARD_POWER -0.8

class MiscOps
{
private:
	frc::Spark * lift = new Spark{LIFT_PWM}; //Instantiate a spark for the lift
	frc::Spark * conveyor = new Spark{CONVEYOR_PWM}; //Instantiate a spark for the conveyor.

public:
	void MoveLift(int angle);
	void LiftStop();
	void MoveConveyor(bool direction);
	void ConveyorStop();
};



#endif /* SRC_MISCOPS_H_ */
