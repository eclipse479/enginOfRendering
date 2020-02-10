#include "camera.h"



camera::camera()
{
	this->setPerspective(90.0f * 3.141f / 180.0f, 16.0f / 9.0f, 0.1f, 50.0f);
	this->setLookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 10.0f, 0.0f));
}

camera::camera(float FOV, float aspectRatio, float close, float distant)
{
	this->setPerspective(FOV, aspectRatio, close, distant);
}

void camera::update(GLFWwindow* window)
{
	//// hide/reveal mouse
	//if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !mouseCatch && timer < 0)
	//{
	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//	mouseCatch = true;
	//	timer = 10;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && mouseCatch && timer < 0)
	//{
	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//	mouseCatch = false;
	//	timer = 10;
	//}
	//if(timer > -1)
	//timer--;	
}

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
	this->projection = glm::perspective(FOV, aspectRatio, close, distant);
	updateProjectionViewTransform();
}
void camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	this->viewTransform = glm::lookAt(from, to, up);
	this->worldTransform = glm::inverse(viewTransform);
	updateProjectionViewTransform();
}
void camera::setPosition(glm::vec3 newPosition)
{
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