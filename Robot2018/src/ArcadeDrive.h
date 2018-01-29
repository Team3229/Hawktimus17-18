#ifndef SRC_ARCADEDRIVE_H_
#define SRC_ARCADEDRIVE_H_

//Standard library includes
#include <iostream>
#include <memory>
#include <string>

//Constants for driving.
#define SAFETY_TIMEOUT 0.01 //Changed to 10 milliseconds as specified in guide
#define MAX_POWER 0.8
#define AUTO_POWER 0.60
#define GYRO_GAIN 0.259
#define COMP_RATIO 0.1111
#define TURN_POWER 0.47

//Constants for other systems.
#define LIFT_POWER 0.8
#define CONVEYOR_FORWARD_POWER 0.5
#define CONVEYOR_BACKWARD_POWER -0.8

//Constants for port numbers and PWMs
#define LEFT_MOTOR_PWM 0
#define RIGHT_MOTOR_PWM 1
#define LIFT_PWM 2
#define CONVEYOR_PWM 3
#define GYRO_SPI_PORT 0

//FRC library includes
#include <Timer.h>
#include <GenericHID.h>
#include <math.h>
#include <RobotDrive.h>
#include <AnalogGyro.h>
#include <Spark.h>
#include <RobotDrive.h>
#include "ctre/Phoenix.h"
//#include "WPI_TalonSRX.h" CTRE guide says is required.  Error "Unresolved inclusion"

class ArcadeDrive
{
public:
	ArcadeDrive();
	~ArcadeDrive();
	void ResetHeading();
	void Stop();
	void Drive(double Y, double X);
	void DriveStraight();
	void DriveTurn (int angle);
	void MoveLift(int angle);
	void LiftStop();
	void MoveConveyor(bool direction);
	void ConveyorStop();

private:
	WPI_TalonSRX * masterLeft = new WPI_TalonSRX(1);
	WPI_TalonSRX * masterRight = new WPI_TalonSRX(2);
	WPI_TalonSRX * slaveLeft = new WPI_TalonSRX(3);
	WPI_TalonSRX * slaveRight = new WPI_TalonSRX(4);

	frc::RobotDrive * myDriveTrain = new RobotDrive(masterLeft, masterRight, slaveLeft, slaveRight);

	/* IN CASE ROBOTDRIVE DOSN'T WORK:
	 *
	 * motorcontrol::ControlMode percent = ControlMode::PercentOutput;  //For brevity
	 * masterLeft->Set(percent, 0); //For stopping
	 * masterRight->Set(percent, 0); //For stopping
	 *
	 * masterLeft->Set(percent, powerLeft);
	 * masterRight->Set(percent, powerRight);
	 *
	 * powerLeft and powerRight will have to be determined by a function that calculates how much power each side needs to have
	 * in order to go in the direction the driver wants. (Vectors and Trignometry!  Yay!)
	 */

	frc::AnalogGyro gyro { GYRO_SPI_PORT }; //Instantiate gyro and initialize its port
	frc::Spark * lift = new Spark{LIFT_PWM}; //Instantiate a spark for the lift
	frc::Spark * conveyor = new Spark{CONVEYOR_PWM}; //Instantiate a spark for the conveyor.
};

#endif /* SRC_ARCADEDRIVE_H_ */
