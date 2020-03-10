#include "camera.h"



camera::camera()
{
	// set view type to perspective and sets up values
	this->setPerspective(90.0f * 3.141f / 180.0f, 16.0f / 9.0f, 0.1f, 25000.0f);
	//starting direction camera is facing
	this->setLookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 10.0f, 0.0f));
}

camera::camera(float FOV, float aspectRatio, float close, float distant)
{
	this->setPerspective(FOV, aspectRatio, close, distant);
}

void camera::update()
{
}

//returns certain values
const glm::mat4& camera::getProjection()
{
	return this->projection;
}
const glm::mat4& camera::getView()
{
	return this->viewTransform;
}
const glm::mat4& camera::getWorldTransform()
{
	return this->worldTransform;
}
const glm::mat4& camera::getProjectionView()
{
	return this->projectionView;
}


void camera::setPerspective(float FOV, float aspectRatio, float close, float distant)
{
	//changes the perspective settings of the camera
	//						Perspective(FieldOfView, ScreenAspectRatio, nearPoint, farPoint)
	this->projection = glm::perspective(FOV, aspectRatio, close, distant);
	updateProjectionViewTransform();
}
void camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	//sets what the camera is looking at
	//						   lookAt(cameraPos, thingToLookAt, directionOfUp)
	this->viewTransform = glm::lookAt(from, to, up);
	this->worldTransform = glm::inverse(viewTransform);
	updateProjectionViewTransform();
}
void camera::setPosition(glm::vec3 newPosition)
{
	//set current position of the camera
	this->worldTransform[3] = glm::vec4(newPosition,1);
	this->viewTransform = glm::inverse(worldTransform);
	updateProjectionViewTransform();
}
void camera::updateProjectionViewTransform()
{
	//view transform is == inverse of world transform
	viewTransform = glm::inverse(worldTransform);
	//update the projection view
	this->projectionView = this->projection * this->viewTransform;
}