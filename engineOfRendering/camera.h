#pragma once
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
class camera
{
public:
	camera();

	~camera();

	void update(GLFWwindow* window);
	
	void findDeltaTime();
	void captureMousePos(GLFWwindow* window, double mouseX, double mouseY);
	
	glm::mat4 returnProjection();
	glm::mat4 returnView();
	glm::mat4 returnModel();

private:
	//		Perspective(FieldOfView, ScreenAspectRatio, nearPoint, farPoint)
	glm::mat4 projection = glm::perspective(90.0f, 16 / 9.0f, 0.1f, 50.0f);
	//		lookAt(cameraPos, thingToLookAt, directionOfUp)
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos+ cameraFront, cameraUp);
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec4 worldSpace = glm::vec4(0, 0, 0, 1) * model;
	float cameraSpeed = 0.1f; 

	float currentFrame = 0;
	float lastFrame = 0;
	float deltaTime = 0;


	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;
	float pitch = 0;
	glm::vec3 direction;
	bool mouseCatch = false;
	int timer = 10;

	bool firstFrame = true;
	float lastX = 400, lastY = 300;
};

