#include "camera.h"
camera::camera()
{
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	currentFrame = 0;
	lastFrame = 0;
	deltaTime = 0;
}

camera::~camera()
{

}
void camera::update(GLFWwindow* window)
{
	// hide/reveal mouse
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !mouseCatch && timer < 0)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		mouseCatch = true;
		timer = 10;
	}
	else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && mouseCatch && timer < 0)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		mouseCatch = false;
		timer = 10;
	}
	timer--;

	//move camera
	cameraSpeed = 3 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		cameraPos += glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
	}
	//set camera position
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//glfwSetCursorPosCallback(window,  captureMousePos);
}

glm::mat4 camera::returnProjection()
{
	return projection;
}
glm::mat4 camera::returnView()
{
	return view;
}
glm::mat4 camera::returnModel()
{
	return model;
}

void camera::findDeltaTime()
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void camera::captureMousePos(GLFWwindow* window, double mouseX, double mouseY)
{
	if (firstFrame)
	{
		lastX = mouseX;
		lastY = mouseY;
		firstFrame = false;
	}

	float xOffset = mouseX - lastX;
	float yOffset = mouseY - lastY;
	lastX = mouseX;
	lastY = mouseY;

	const float sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;


	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}