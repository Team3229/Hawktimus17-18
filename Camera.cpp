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

Camera::Camera()
{
	cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera("axis-camera.local");

	// Set the camera settings
	//CameraServer::GetInstance()->SetSize(SIZE);
	camera.SetFPS(FPS);
	camera.SetWhiteBalanceAuto();
	camera.SetExposureAuto();
	camera.SetBrightness(BRIGHTNESS);
	CameraServer::GetInstance()->StartAutomaticCapture();
}
