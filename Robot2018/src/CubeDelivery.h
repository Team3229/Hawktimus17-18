/*
 * File Name:                        CubeDelivery.h
 * Author(s):                        Luke Simone
 * Last Modified:                    2/13/2018
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
#include <WPILib.h>
#include <Spark.h>

class CubeDelivery
{
public:
	enum LiftDirection {Up, Down};

	CubeDelivery();
	~CubeDelivery();
	void Lift(LiftDirection directon);
	void StopLift();
	void Conveyor(double& conveyorPower);
	void StopConveyor();
	void TestLimitSwitch();

	//Automated functions
	void PushCube();
	void ResetLift();
	void LiftToScale();
	void LiftToSwitch();

private:
	frc::DigitalInput * topSwitch; //Instantiate switch at top of the robot
	frc::DigitalInput * bottomSwitch; //Instantiate switch at bottom of the robot

	frc::Spark * myLift; //Instantiate lift motor
	frc::Spark * myConveyor; //Instantiate conveyor motor

	frc::Timer switchTime{};
	frc::Timer scaleTime{};

	//Constants for PWM ports
	const short TOPSWITCH_DIO = 0;
	const short BOTTOMSWITCH_DIO = 1;
	const short LIFT_PWM = 2;
	const short CONVEYOR_PWM = 0;

	//Constants for power and max power
	const float LIFT_POWER = 1.0;
	const float CONVEYOR_POWER = 1.0; //Conveyor forward at max power

	//Time constants PLACEHOLDERS
	const float PUSH_TIME = 1.0; //Time the conveyor will run to push the cube out
	const float SC_LIFT_TIME = 1.0; //Time it takes to move lift from lowest to the height of the scale
	const float SW_LIFT_TIME = 1.0; //Time it takes to move lift from lowest point to the height of the switch
	bool firstSwitch = true;
	bool firstScale = true;
};

#endif /* SRC_CUBEDELIVERY_H_ */
