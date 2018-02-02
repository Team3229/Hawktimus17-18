/*
 * CubeDelivery.h
 *
 *  Created on: Feb 1, 2018
 *      Author: luke
 */

#ifndef SRC_CUBEDELIVERY_H_
#define SRC_CUBEDELIVERY_H_

//regular includes
#include <iostream>
#include <memory>
#include <string>

//frc includes
#include <XboxController.h>
#include <Timer.h>
#include <WPILib.h>
#include <Spark.h>

class CubeDelivery
{
public:
	CubeDelivery();
	~CubeDelivery();
	void Lift();
	void StopLift();
	void Conveyor(float Y);
	void StopConveyor();

private:
	DigitalInput * topSwitch; //Instantiate switch at top of the robot
	DigitalInput * bottomSwitch; //Instantiate switch at bottom of the robot

	frc::Spark * myLift; //Instantiate motor for the lift
	frc::Spark * myConveyor; //Instantiate motor for the conveyor

	const float TOPSWITCH_DIO = 0; //Digital input
	const float BOTTOMSWITCH_DIO = 1; //Digital input
	const float MAX_POWER = 0.6; //Maximum allowed motor power for the 2 sparks
	const float LIFT_PWM = 0; //Placeholder
	const float CONVEYOR_PWM = 0; //Placeholder
};

#endif /* SRC_CUBEDELIVERY_H_ */
