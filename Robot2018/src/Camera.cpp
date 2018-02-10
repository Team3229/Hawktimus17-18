/*
 * File:		Camera.cpp
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Controls the camera on the driver station.
 */

#include "Camera.h"
using namespace frc;

Servo * panServo;
Servo * tiltServo;

Camera::Camera()
{
	panServo = new Servo(PAN_SERVO_PWM);
	tiltServo = new Servo(TILT_SERVO_PWM);
	cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera("axis-camera.local");

	// Set the camera settings
	//CameraServer::GetInstance()->SetSize(SIZE);
	camera.SetFPS(FPS);
	camera.SetWhiteBalanceAuto();
	camera.SetExposureAuto();
	camera.SetBrightness(BRIGHTNESS);
	CameraServer::GetInstance()->StartAutomaticCapture();
}

void Camera::Reset()
{
	std::cout << "Camera Reset()" << std::endl;

	panServo->Set(INITIAL_PAN);
	tiltServo->Set(INITIAL_TILT);
}

void Camera::Move (double tilt, double pan)
{
	std::cout << "Camera Move()" << std::endl;

	// Move toward desired position
	if (pan > 0)
	{
		panServo->Set(panServo->Get() + PANTILT_RATE);
	}
	else
	{
		panServo->Set(panServo->Get() - PANTILT_RATE);
	}
	if (tilt < 0) // tilt is reversed on Xbox controller
	{
		tiltServo->Set(tiltServo->Get() + PANTILT_RATE);
	}
	else
	{
		tiltServo->Set(tiltServo->Get() - PANTILT_RATE);
	}
}
