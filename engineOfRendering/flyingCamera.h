#pragma once
#include "camera.h"

#ifndef FLY_CAMERA_H
class flyingCamera :	public camera
{
public:
	void update(float deltaTime);
	void setSpeed(float newSpeed);
private:

	float speed = 10.0f;

	float angularSpeed = 0.01f;
};

#endif // !FLY_CAMERA_H
