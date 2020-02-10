#pragma once
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
class camera
{
public:
	camera();

	camera(float FOV, float aspectRatio, float close, float distant);

	void update(GLFWwindow* window);
	void setPerspective(float FOV, float aspectRatio, float close, float distant);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 newPosition);


	const glm::mat4& getWorldTransform();
	const glm::mat4& getView();
	const glm::mat4& getProjection();
	const glm::mat4& getProjectionView();
protected:
	//		Perspective(FieldOfView, ScreenAspectRatio, nearPoint, farPoint)
	glm::mat4 projection;// = glm::perspective(90.0f, 16 / 9.0f, 0.1f, 50.0f);
	//		lookAt(cameraPos, thingToLookAt, directionOfUp)
	glm::mat4 view;// = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	glm::mat4 projectionView = projection * view;


	void updateProjectionViewTransform();
	glm::mat4 worldTransform = glm::mat4(0.0f);
	bool mouseCatch = false;
	int timer = 10;


};

