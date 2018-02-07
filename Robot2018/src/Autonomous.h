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
#include <AnalogInput.h>

//Programmer-Defined Includes
#include "DriveSystem.h"

class Autonomous
{
private:
	//Constants for driving
	const double TURN_ANGLE = 30;
	const double DRIVE_DISTANCE = 0.0;
	const int BASELINE = 8;

	//Constants for ports
	const int ULTRA_PORT = 2;

	ADXRS450_Gyro * gyro; //Instantiates gyro
	frc::SendableChooser<int> * chooser; //Receiving from the smart dashboard
	Timer movementTimer(); //For tracking movements.
	AnalogInput * ultra; //Gets input from distance sensor on AnalogPort

	//Enums from dashboard
	enum Position {C, L, R}; //For determining which station we are at
	enum Target {E, S, B, D}; //For determining which action we want to take.
	enum Delay {Yes, No}; //For determining if delay

	//Initializations of enums
	Position start;
	Target procedure;
	Delay wait;

	char switchColor; //Color of the switch

public:
	Autonomous();
	~Autonomous();
	void AutoInit(std::string colors);
	void ReadStation();
	void AutoPeriodic();
	void Exchange();
	void Switch ();
	void Baseline();
};

#endif /*SRC_AUTONOMOUS_H*/
