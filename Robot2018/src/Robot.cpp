/*
 * File:			Robot.cpp
 * Author(s):		Hayden Mann
 * Last Modified:	02/02/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the default class for running the robot through the roboRIO for the 2018 build season
 */

#include <Robot.h>

class Robot : public frc::IterativeRobot
{
private:
	//Constants for controller
	const float DEAD_BAND_LEFT = 0.1;
	const float DEAD_BAND_RIGHT = 0.075;
	const int XBOX_USB_PORT = 0;

	//Instantiate XBOX Controller
	XboxController xbox{XBOX_USB_PORT};

	//Instantiate Climber
	Climber climberMotor{};

	//Instantiate Autonomous mode
	Autonomous autoMode{};

	//Instantiate Chasis (drive train)
	DriveSystem chasis{};

	//Instantiate camera
	Camera driveCam{};

	//Instantiate object to control conveyor and lift system.
	CubeDelivery gettinPoints{};

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
		//autoMode.DoAutonomousPeriodic(&chasis);
	}

	//Runs once Teleop starts
	void TeleopInit()
	{
		std::cout << "TeleopInit()" << std::endl;
	}

	//Runs continually during Teleop
	void TeleopPeriodic()
	{
		double leftY, leftX, rightY; //An x and y coordinate.
		std::cout << "TeleopPeriodic()" << std::endl;

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
		if (xbox.GetYButton()) //Map the right hand "bumper" (trigger) button to the climber PWM, button is pressed.
		{
			climberMotor.Climb(); //Climb
		}
		else
		{
			climberMotor.Stop(); //button released
		}

		//Map right joystick for the conveyor
		rightY = xbox.GetRawAxis(5);
		if(abs(rightY) > DEAD_BAND_RIGHT)
		{
			gettinPoints.Conveyor(rightY);
		}
		else
		{
			gettinPoints.StopConveyor();
		}

		//Map the left and right bumper to the climbers
		if(xbox.GetBumper(GenericHID::kRightHand))
		{
			gettinPoints.Lift(true);
		}
		else if(xbox.GetBumper(GenericHID::kLeftHand))
		{
			gettinPoints.Lift(false); //Move lift system down.
		}
		else
		{
			gettinPoints.StopLift();
		}

		Wait(0.05);
	}

	//Test mode
	void TestPeriodic()
	{
		std::cout << "TestPeriodic()" << std::endl;
	}

};

START_ROBOT_CLASS(Robot);
