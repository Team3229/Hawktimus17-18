/*
 * File:			Robot.h
 * Author:			Hayden Mann
 * Last Modified:	02/02/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * This file contains the necessary includes that are needed to execute the code written in Robot.cpp.  It does NOT define the class itself.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

//Standard library includes
#include <iostream>
#include <string>
#include <fstream>

//Includes from the frc namespace
#include <IterativeRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <XboxController.h>
#include <Timer.h> //For wait function
#include <AnalogInput.h>
#include <ADXRS450_Gyro.h>

//Includes from programmer-defined files.
#include "Climber.h"
#include "Autonomous.h"
#include "Camera.h"
#include "CubeDelivery.h"
#include "DriveSystem.h"
#include "Debug.h"

class Robot : public frc::IterativeRobot {
public:
	void RobotInit() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
	void WriteLogFile( const std::string &text )
	{
	    std::ofstream log_file(
	        "log_file.txt", std::ios_base::out | std::ios_base::app );
	    log_file << text << std::endl;
	}

private:
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;

	//Constants for controller
	const float DEAD_BAND_LEFT = 0.1;
	const float DEAD_BAND_RIGHT = 0.1;
	const int XBOX_USB_PORT = 0; //Current Driver 1 port
	const float START_LOCK_TIME = 1.5; //Time that the lift will lock climbing
	//const int DRIVER2_XBOX_USB_PORT = 1;

	//Instantiate XBOX Controller
	XboxController xbox{XBOX_USB_PORT};

	//Driver 2 controller
	//XboxController driver2Xbox{DRIVER2_XBOX_USB_PORT};

	//Instantiate Climber and it's timer
	Climber climberMotor{};

	//Instantiate Chasis (drive train)
	DriveSystem chasis{};

	//Instantiate object to control conveyor and lift system.
	CubeDelivery gettinPoints{};

	//Instantiate Autonomous mode
    Autonomous autoMode{&chasis, &gettinPoints};

	//Instantiate camera
	Camera driveCam{};
};

#endif /* SRC_ROBOT_H_ */
