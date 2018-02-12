/*
 * File Name:                        CubeDelivery.h
 * Author(s):                        Luke Simone
 * Last Modified:                    2/3/2018
 * Team:                             Hawktimus Prime - 3229
 *
 * File Description:
 * Defines the class and the necissary includes used by CubeDelivery.cpp,
 * instantiates the switches and motors, and defines needed constants.
 */

#ifndef SRC_CUBEDELIVERY_H_
#define SRC_CUBEDELIVERY_H_

//regular includes
#include <iostream>
#include <memory>
#include <string>

//frc includes
#include <Timer.h>
#include <WPILib.h>
#include <Spark.h>

class CubeDelivery
{
public:
	CubeDelivery();
	~CubeDelivery();
	void ResetLift();
	void Lift(const bool directon);
	void StopLift();
	void Conveyor(double& conveyorPower);
	void StopConveyor();

private:
	Timer resetTimer(); //Creates a timer that we'll use for resetting the lift

	DigitalInput * topSwitch; //Instantiate switch at top of the robot
	DigitalInput * bottomSwitch; //Instantiate switch at bottom of the robot

	frc::Spark * myLift; //Instantiate lift motor
	frc::Spark * myConveyor; //Instantiate conveyor motor

	//Constants for PWM ports
	const float TOPSWITCH_DIO = 0;
	const float BOTTOMSWITCH_DIO = 1;
	const float LIFT_PWM = 2;
	const float CONVEYOR_PWM = 0;

	//Constants for power and max power
	const float MAX_POWER = 0.6;
	const float LIFT_POWER = 1.0;
	const float CONVEYOR_POWER = 0.6; //NOT CURRENTLY USED
};

#endif /* SRC_CUBEDELIVERY_H_ */
