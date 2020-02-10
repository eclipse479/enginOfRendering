#include "flyingCamera.h"

void flyingCamera::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void flyingCamera::update(float deltaTime)
{
	// Grab context
	auto glfw_window = glfwGetCurrentContext();
	//build transformation vector
	glm::vec4 displacement = glm::vec4(0.0f,0.0f,0.0f,0.0f);

	speed = 3 * deltaTime;

		//moves the camera in the opposite direction the camera is facing
		displacement.y -= glfwGetKey(glfw_window, GLFW_KEY_UP);
		//moves the camera in the direction the camera is facing
		displacement.y += glfwGetKey(glfw_window, GLFW_KEY_DOWN);
		//moves the camera perpandicular to both the direction the camera is facing and the Up vector
		displacement.x += glfwGetKey(glfw_window, GLFW_KEY_RIGHT);
		//moves the camera perpandicular to both the direction the camera is facing and the Up vector
		displacement.x -= glfwGetKey(glfw_window, GLFW_KEY_LEFT);
	//set camera position
	    this->worldTransform[3] - (displacement * speed);

	updateProjectionViewTransform();
}