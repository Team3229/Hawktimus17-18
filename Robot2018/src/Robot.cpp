/*
 * File:			Robot.cpp
 * Author(s):		Programming Subteam
 * Last Modified:	01/28/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the default class for the Robot where First will run all of its required methods.
 */

#include <Robot.h>

class Robot : public frc::IterativeRobot
{
private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();

	//Constants for controller
	const float DEAD_BAND_LEFT = 0.1;
	const float DEAD_BAND_RIGHT = 0.75;
	const int XBOX_USB_PORT = 0;

	//Instantiate XBOX Controller
	XboxController xbox{XBOX_USB_PORT};

	//Instantiate Climber
	Climber climberMotor{};

	//Instantiate Autonomous mode
	Autonomous autoMode{};

	//Instantiate Chasis (drive train)
	ArcadeDrive chasis{};

	//Instantiate camera
	Camera driveCam{};

public:

	//Runs once on first boot of Robot
	void RobotInit()
	{
		std::cout << "RobotInit()" << std::endl;

		//Display the Autonomous Selection Options on Driver Station
		autoMode.AutoSelectInit();

	}

	//Runs once when Autonomous starts
	void AutonomousInit() override //Override - Adds virtuality to the base class and will override any function with the same name, streamlining our method to the top of the method hierarchy.
	{
		std::cout << "AutonomousInit()" << std::endl;

		//Get the Autonomous Selection from the Driver Station
		autoMode.DoAutonomousInit();
	}

	//Runs continually during Autonomous
	void AutonomousPeriodic()
	{
		std::cout << "AutonomousPeriodic()" << std::endl;

		//While autonomous movements are not done (because it is re-entrant)
		autoMode.DoAutonomousPeriodic(&chasis);
	}

	//Runs once Teleop starts
	void TeleopInit()
	{
		std::cout << "TeleopInit()" << std::endl;
	}

	//Runs continually during Teleop
	void TeleopPeriodic()
	{
		float leftY, leftX, rightY; //An x and y coordinate.
		std::cout << "TeleopPeriodic()" << std::endl;

		//frc::Scheduler::GetInstance()->Run();

		//Drive (left hand joystick on the controller)
		//Get both the x and y coordinates from the left joystick.
		leftY = xbox.GetY(GenericHID::kLeftHand);
		leftX = xbox.GetX(GenericHID::kLeftHand);
		if(abs(leftX) > DEAD_BAND_LEFT && abs(leftY) > DEAD_BAND_LEFT)
		{
			chasis.Drive(leftY, leftX);
		}
		else
		{
			chasis.Stop();
		}

		//Climber (right hand "bumper" button)
		if (xbox.GetBumper(GenericHID::kRightHand)) //Map the right hand "bumper" (trigger) button to the climber PWM, button is pressed.
		{
				climberMotor.Climb(); //Climb
		}
		else
		{
			climberMotor.Stop(); //button released
		}

		//Map right joystick for the conveyor
		rightY = xbox.GetY(GenericHID::kRightHand);
		if(abs(rightY) > DEAD_BAND_RIGHT)
		{
			//CubeSystem
		}
		else
		{
			//CubeSystem
		}

		//Map Right Trigger for lift system.
		if(xbox.GetTriggerAxis(GenericHID::kRightHand)) //If the trigger is pressed
		{
			//CubeSystem
		}
		else
		{
			//CubeSystem
		}

		//Map Left Trigger
		/*if(leftTrigger.GetTriggerPressed()) //If the trigger is pressed
		{
			if(safetyWait())
				chasis.MoveConveyor(false); //Move the conveyor backwards (false).
		}
		else
		{
			count = 0;
			chasis.ConveyorStop();
		}*/

		Wait(0.05);
	}

	//Test mode
	void TestPeriodic()
	{
		std::cout << "TestPeriodic()" << std::endl;

		//Removed "lw->Run()".  Error message stated that it was deprecated and no longer necessary.
	}

};

START_ROBOT_CLASS(Robot);
