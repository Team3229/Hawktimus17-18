/*
 * File:			Robot.h
 * Author:			Neil Anderson
 * Version:			1.0
 * Last Modified:	01/16/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * This file defines all necessary macro constants for the Robot.cpp file as well as includes all necessary external libraries.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

//Standard library includes
#include <iostream>
#include <string>

//Includes from the frc namespace
#include <IterativeRobot.h>
#include <XboxController.h>
#include <LiveWindow/LiveWindow.h>
#include <Timer.h> //For wait function
#include <Joystick.h>
#include <ctre/Phoenix.h>


//Includes from programmer-defined files.
#include "Climber.h"
#include "ArcadeDrive.h"
#include "Autonomous.h"
#include "Camera.h"

#endif /* SRC_ROBOT_H_ */
