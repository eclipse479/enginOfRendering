#pragma once
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"

#ifndef CAMERA_H
class camera
{
public:
	camera();

	camera(float FOV, float aspectRatio, float close, float distant);

	virtual void update(GLFWwindow* window);
	void setPerspective(float FOV, float aspectRatio, float close, float distant);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 newPosition);


	const glm::mat4& getWorldTransform();
	const glm::mat4& getView();
	const glm::mat4& getProjection();
	const glm::mat4& getProjectionView();
protected:
	glm::mat4 worldTransform = glm::mat4(0.0f);
	//		Perspective(FieldOfView, ScreenAspectRatio, nearPoint, farPoint)
	glm::mat4 projection;
	//		lookAt(cameraPos, thingToLookAt, directionOfUp)
	glm::mat4 viewTransform;
	glm::mat4 projectionView = projection * viewTransform;
	
	void updateProjectionViewTransform();
	bool mouseCatch = false;
	int timer = 10;
};

#endif // !CAMERA_H