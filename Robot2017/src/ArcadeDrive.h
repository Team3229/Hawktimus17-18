#ifndef SRC_ARCADEDRIVE_H_
#define SRC_ARCADEDRIVE_H_

//Standard library includes
#include <iostream>
#include <memory>
#include <string>

//Constants for driving.
#define SAFETY_TIMEOUT 0.500
#define MAX_POWER 0.8
#define AUTO_POWER 0.60
#define GYRO_GAIN 0.259
#define COMP_RATIO 0.1111
#define TURN_POWER 0.47

//Constants for port numbers and PWMs
#define LEFT_MOTOR_PWM 0
#define RIGHT_MOTOR_PWM 1
#define GYRO_SPI_PORT 0

//FRC library includes
#include <Timer.h>
#include <GenericHID.h>
#include <math.h>
#include <RobotDrive.h>
#include <AnalogGyro.h>

class ArcadeDrive
{
public:
	ArcadeDrive();
	void ResetHeading();
	void Stop();
	void Drive(double Y, double X);
	void DriveStraight();
	void DriveTurn (int angle);

private:
	frc::RobotDrive myDriveTrain {LEFT_MOTOR_PWM, RIGHT_MOTOR_PWM};
	frc::AnalogGyro gyro { GYRO_SPI_PORT };
};

#endif /* SRC_ARCADEDRIVE_H_ */
