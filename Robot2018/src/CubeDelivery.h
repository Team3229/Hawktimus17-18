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

	//Automated functions
	void PushCube();
	void LiftToScale();
	void LiftToSwitch();

private:
	frc::Timer pushTime{}; //Creates a timer for pushing the cube
	frc::Timer resetTime{}; //Creates a timer that we'll use for resetting the lift
	frc::Timer switchTime{}; //Creates timer for lifting the lift to the switch
	frc::Timer scaleTime{}; //Creates timer for lifting to the scale

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
	const float CONVEYOR_POWER = -0.6;

	//Time constants PLACEHOLDERS
	const float PUSH_TIME = 1.0; //Time the conveyor will run to push the cube out
	const float SC_LIFT_TIME = 1.0; //Time it takes to move lift from lowest to the height of the scale
	const float SW_LIFT_TIME = 1.0; //Time it takes to move lift from lowest point to the height of the switch
};

#endif /* SRC_CUBEDELIVERY_H_ */
