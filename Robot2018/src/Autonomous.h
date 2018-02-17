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

#define FORWARD true
#define REVERSE false
#define DRIVE_FT_SEC 6.0
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

	DriveSystem * driveTrain;
	CubeDelivery * gettinPoints;
	Timer autoTimer{};

	const double TIME_LIMIT = 0.0; //Move for how long?
	double timeLimit = 0.0;
	const static int POSITION_SIZE = 3;
	const static int TARGET_SIZE = 6;
	const static int MOVEMENT_SIZE = 10;
	const float COMPENSATE_TIME = (1/2) * driveTrain->SMOOTH_TIME; //Should cancel out ramp up time for driving straight

	char switchColor; //Color of the switch
	char scaleColor; //color of scale

	//Choosing bois
	frc::SendableChooser<int> * positionChooser; //Receiving from the smart dashboard
	frc::SendableChooser<int> * targetChooser;
	frc::SendableChooser<int> * delayChooser;

	enum positions {left, center, right};
	enum targets {baseline, exchange, leftswitch, rightswitch, leftscale, rightscale};
	enum movements {M1, M2, M3, M4, M5, M6, M7, M8, M9, M10};

	enum commands {drive, reverse, turn, lift, lower, push, done};

	struct cmd {
		commands command;
		double data; 	/* feet or degrees */
	};

	cmd autocommand [POSITION_SIZE] /* position */ [TARGET_SIZE] /* target */ [MOVEMENT_SIZE]; /* movement */

	bool autodone = false; //Is movement done?
	bool useDelay = false; //Delay our auto?
	int movement = 0; //What movement are we on?
	targets target = baseline;
	positions position = center;


public:
	Autonomous(DriveSystem * chasis, CubeDelivery * cube);
	~Autonomous();
	void AutoInit(std::string colors);
	void ReadStation();
	void AutoPeriodic();
	void AddOptions();
	void SetupAutoCommands();
};

#endif /*SRC_AUTONOMOUS_H*/

//Ultrasonic output WORKING
		/* double currentDistance = ultra.GetValue() * ValueToInches;
		std::cout << "Ultrasonic distance: " << currentDistance << std::endl; */

		//Gyro testing area WORKING
		/* int currentAngle = gyro->GetAngle();
		std::cout << "Gyro reading: " << currentAngle << std::endl; */
