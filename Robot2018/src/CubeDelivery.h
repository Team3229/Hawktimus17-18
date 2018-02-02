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
#include <Math.h>

//frc includes
#include <Timer.h>
#include <WPILib.h>
#include <Spark.h>

class CubeDelivery
{
public:
	CubeDelivery();
	~CubeDelivery();
	void Lift(const bool directon);
	void StopLift();
	void Conveyor(double &conveyorPower);
	void StopConveyor();

private:
	DigitalInput * topSwitch; //Instantiate switch at top of the robot
	DigitalInput * bottomSwitch; //Instantiate switch at bottom of the robot

	frc::Spark * myLift; //Instantiate motor for the lift
	frc::Spark * myConveyor; //Instantiate motor for the conveyor

	const float TOPSWITCH_DIO = 0; //Digital input for top switch
	const float BOTTOMSWITCH_DIO = 1; //Digital input for bottom switch
	const float MAX_POWER = 0.6; //Maximum allowed motor power for the sparks
	const float LIFT_POWER = 0.6; //Lift power
	const float CONVEYOR_POWER = 0.6; //Conveyor power NOT USED
	const float LIFT_PWM = 0; //PWM for lift motor NOT CORRECT
	const float CONVEYOR_PWM = 0; //PWM for conveyor NOT CORRECT
};

#endif /* SRC_CUBEDELIVERY_H_ */
