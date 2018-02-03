#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include <iostream>
#include <memory>
#include <string>

// Constants for Camera Settings
#define SIZE 1080 // 640 x 480
#define FPS 12
#define BRIGHTNESS 40

// Constants for Pan/Tilt Servos
#define PAN_SERVO_PWM 3
#define TILT_SERVO_PWM 4
#define INITIAL_PAN 0.2
#define INITIAL_TILT 0.5
#define PANTILT_RATE 0.05

#include <GenericHID.h>
#include <math.h>
#include <Servo.h>
#include <CameraServer.h>

class Camera
{
public:
	Camera();
	void Reset();
	void Move(double Y, double X);

private:
	frc::Servo * panServo;
	frc::Servo * tiltServo;
};

#endif /* SRC_CAMERA_H_ */
