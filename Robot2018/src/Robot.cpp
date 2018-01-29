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

	//Instantiate XBOX Controller
	XboxController xbox{XBOX_USB_PORT};

	//Instantiate Climber
	Climber climberMotor{};

	//Instantiate Autonomous mode
	Autonomous autoMode{};

	//Instantiate Chasis (drive train)
	ArcadeDrive chasis{};

	//Instantiate Joysticks for mapping Right Trigger and Left Trigger
	Joystick rightTrigger{3}, leftTrigger{2};

	//Counter for safety wait.
	int count = 0;

	//Allows us to wait for a certain number of iterations to climb.
	bool safetyWait()
	{
		if(count < 25) //Test to see if the count is less than 25, meaning we CANNOT go.
		{
			count++; //Increase count to count to 25 iterations
			return false; //We can't go
		}
		else
			return true; //We have reached our time, we can go.
	}

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
		double Y, X; //An x and y coordinate.
		std::cout << "TeleopPeriodic()" << std::endl;

		//Drive (left hand joystick on the controller)
		//Get both the x and y coordinates from the left joystick.
		Y = xbox.GetY(GenericHID::kLeftHand);
		X = xbox.GetX(GenericHID::kLeftHand);
		if((abs(Y) > DEAD_BAND) || (abs(X) > DEAD_BAND)) //As long as the absolute value of the coordinate is not in the deadband.
		{
			//Driver joystick input.
			chasis.Drive(Y, X); //Call drive, passing the given coordinate.
		}
		else
		{
			chasis.Stop(); //No joystick input, stop moving.
		}

		//Climber (right hand "bumper" button)
		if (xbox.GetBumper(GenericHID::kRightHand)) //Map the right hand "bumper" (trigger) button to the climber PWM, button is pressed.
		{
			if(safetyWait()) //If we have exceeded our wait period.
				climberMotor.Climb(); //Climb
		}
		else
		{
			climberMotor.Stop(); //button released
			count = 0;
		}

		//Mapping up DPAD button
		if(xbox.GetPOV(0) != -1)
		{
			if(safetyWait())
				chasis.MoveLift(xbox.GetPOV(0));
		}
		else
		{
			count = 0;
			chasis.LiftStop(); //Stop moving the lift
		}

		//Mapping Down DPAD button
		if(xbox.GetPOV(180) != -1)
		{
			if(safetyWait())
				chasis.MoveLift(xbox.GetPOV(180));
		}
		else
		{
			count = 0;
			chasis.LiftStop(); //Stop moving the lift
		}

		//Map Right Trigger
		if(rightTrigger.GetTriggerPressed()) //If the trigger is pressed
		{
			if(safetyWait())
				chasis.MoveConveyor(true); //Move the conveyor forward (true)
			else
			{
				count = 0;
				chasis.ConveyorStop(); //Stop conveyor
			}
		}

		//Map Left Trigger
		if(leftTrigger.GetTriggerPressed()) //If the trigger is pressed
		{
			if(safetyWait())
				chasis.MoveConveyor(false); //Move the conveyor backwards (false).
		}
		else
		{
			count = 0;
			chasis.ConveyorStop();
		}

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
