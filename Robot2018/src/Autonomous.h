/*
 * File:		Autonomous.h
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Defines the class for autonomous mode that will be instantiated to drive the robot without a human interface.
 */

#ifndef SRC_AUTONOMOUS_H
#define SRC_AUTONOMOUS_H

//Standard Includes
#include <iostream>
#include <string>
#include <Math.h>

//FRC-Defined includes
#include <Timer.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <AnalogInput.h>

//Programmer-Defined Includes
#include "DriveSystem.h"
#include "CubeDelivery.h"

class Autonomous
{
private:

	Timer movementTimer{}; //For tracking movements
	DriveSystem * driveTrain;
	CubeDelivery * gettinPoints;

	//Choosing bois
	frc::SendableChooser<int*> * positionChooser; //Receiving from the smart dashboard
	frc::SendableChooser<int*> * targetChooser;
	frc::SendableChooser<int*> * delayChooser;

	//Enums from dashboard
	enum Position {C, L, R}; //For determining which station we are at
	enum Target {D, E, SW, SC, B}; //For determining which action we want to take.
	enum Delay {Yes, No}; //For determining if delay

	//Initializations of enums
	Position start;
	Target procedure;
	Delay wait;

	bool turn = true; //For measuring if this is the first iteration of the DriveTurn method



public:
	Autonomous(DriveSystem * chasis, CubeDelivery * cube);
	~Autonomous();
	void AutoInit(std::string colors);
	void ReadStation();
	void AutoPeriodic();
	void Exchange();
	void Switch ();
	void Baseline();
	void AddOptions();
	char switchColor; //Color of the switch
	char scaleColor; //color of scale

};

#endif /*SRC_AUTONOMOUS_H*/

//Ultrasonic output WORKING
		/* double currentDistance = ultra.GetValue() * ValueToInches;
		std::cout << "Ultrasonic distance: " << currentDistance << std::endl; */

		//Gyro testing area WORKING
		/* int currentAngle = gyro->GetAngle();
		std::cout << "Gyro reading: " << currentAngle << std::endl; */
