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
#include <ADXRS450_Gyro.h>
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
	//Constants for driving
	const double TURN_ANGLE = 30;
	const double DRIVE_DISTANCE = 0.0;
	const int BASELINE = 8;

	//Constants for ports
	const int ULTRA_PORT = 2;
	//const int GYRO_PORT = 1; //Green gyro

	//Sensor constants
	const float GYRO_GAIN = 0.259;
	static constexpr double ValueToInches = 0.125; //Because 8 units per inch of reading 52 MINIMUM (6.5 inches)

	ADXRS450_Gyro * gyro; //Instantiates gyro
	Timer movementTimer(); //For tracking movements.
	AnalogInput * ultra; //Gets input from distance sensor on AnalogPort
	DriveSystem chasis{};
	CubeDelivery gettinPoints{};

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

	char switchColor; //Color of the switch
	char scaleColor; //color of scale

public:
	Autonomous();
	~Autonomous();
	void AutoInit(std::string colors);
	void ReadStation();
	void AutoPeriodic(DriveSystem& chasis);
	void Exchange();
	void Switch ();
	void Baseline();
	void AddOptions();
};

#endif /*SRC_AUTONOMOUS_H*/


//Gyro stuff
		/* gyro->SetSensitivity(GYRO_GAIN);
		gyro->Reset();

		//ultrasonic stuff
		ultra = new Ultrasonic(1, 1); // assigns ultra to be an ultrasonic sensor which uses DigitalOutput 1 for the echo pulse and DigitalInput 1 for the trigger pulse
		ultra->SetEnabled(true);
		ultra->SetAutomaticMode(true); // turns on automatic mode */


//Ultrasonic output WORKING
		/* double currentDistance = ultra.GetValue() * ValueToInches;
		std::cout << "Ultrasonic distance: " << currentDistance << std::endl; */

		//Gyro testing area WORKING
		/* int currentAngle = gyro->GetAngle();
		std::cout << "Gyro reading: " << currentAngle << std::endl; */
