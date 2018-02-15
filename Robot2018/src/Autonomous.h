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

#define FORWARD 0.6
#define REVERSE -0.6
#define DRIVE_FT_SEC 4.0
#define LIFT_FT_SEC 4.0
#define TURN_TIMEOUT 1.0

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
	Timer autoTimer{};

	//Choosing bois
	frc::SendableChooser<int*> * positionChooser; //Receiving from the smart dashboard
	frc::SendableChooser<int*> * targetChooser;
	frc::SendableChooser<int*> * delayChooser;

	enum positions {left, center, right};
	enum targets {baseline, exchange, leftswitch, rightswitch, leftscale, rightscale};
	enum movements {M1, M2, M3, M4, M5, M6, M7, M8, M9, M10};

	enum commands {drive, reverse, turn, lift, lower, push, done};

	struct cmd {
		commands command;
		double	         data; 	/* feet or degrees */
	};
	cmd autocommand [3] /* position */ [6] /* target */ [10]; /* movement */

	bool autodone = false; //Is movement done?
	const double TIME_LIMIT = 0.0; //Move for how long?
	movements movement = M1; //What movement are we on?
	targets target = baseline;


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
