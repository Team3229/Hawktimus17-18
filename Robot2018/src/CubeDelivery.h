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
	void Lift();
	void Conveyor();

	~CubeDelivery()
	{
		delete topSwitch;
		delete bottomSwitch;
		delete myLift;
		delete myConveyor;
	}

private:
	DigitalInput * topSwitch; //Instantiate switch at top of the robot
	DigitalInput * bottomSwitch; //Instantiate switch at bottom of the robot

	frc::Spark * myLift; //Instantiate motor for the lift
	frc::Spark * myConveyor; //Instantiate motor for the conveyor

	const float MAX_POWER = 0.6;
	const float LIFT_PWM = 0;
	const float CONVEYOR_PWM = 0;
	//float Y;
};


#endif /* SRC_CUBEDELIVERY_H_ */
