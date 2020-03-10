#pragma once
#include "camera.h"

#ifndef FLY_CAMERA_H
class flyingCamera :	public camera
{
public:
	//allows camera to change as inputs are used
	void update(float deltaTime);
	//changes the movement speed of the camera
	void setSpeed(float newSpeed);
	//gets the current positon the camera is at
	glm::vec3 getPosition();
private:
	//speed which the camera moves at
	float speed = 10.0f;
	//speed which the camera rotates when the mouse is moved
	float angularSpeed = 0.01f;
};

#endif // !FLY_CAMERA_H
