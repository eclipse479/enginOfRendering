#pragma once
#include "camera.h"
class flyingCamera :	public camera
{
public:
	void update(float deltaTime);
	void setSpeed(float newSpeed);
private:

	float speed = 1.0f;

	float angularSpeed = 0.1f;
};

