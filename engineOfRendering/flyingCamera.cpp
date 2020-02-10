#include "flyingCamera.h"

void flyingCamera::setSpeed(float newSpeed)
{
	this->speed = newSpeed;
}

void flyingCamera::update(float deltaTime)
{
	// Grab context
	auto glfw_window = glfwGetCurrentContext();
	//build transformation vector
	glm::vec4 displacement = glm::vec4(0.0f,0.0f,0.0f,0.0f);

		//moves the camera in the opposite direction the camera is facing
		displacement.y += glfwGetKey(glfw_window, GLFW_KEY_UP);
		//moves the camera in the direction the camera is facing
		displacement.y -= glfwGetKey(glfw_window, GLFW_KEY_DOWN);
		//moves the camera perpandicular to both the direction the camera is facing and the Up vector
		displacement.x += glfwGetKey(glfw_window, GLFW_KEY_RIGHT);
		//moves the camera perpandicular to both the direction the camera is facing and the Up vector
		displacement.x -= glfwGetKey(glfw_window, GLFW_KEY_LEFT);
		//moves the camera perpandicular to both the direction the camera is facing and the Up vector
		displacement.z += glfwGetKey(glfw_window, GLFW_KEY_O);
		//moves the camera perpandicular to both the direction the camera is facing and the Up vector
		displacement.z -= glfwGetKey(glfw_window, GLFW_KEY_P);
	//set camera position
	    this->worldTransform[3] -= (displacement * speed * deltaTime);
		//only update view transform if directional input has been recieved
		if (displacement != glm::vec4(0.0f)) 
		{
			updateProjectionViewTransform();
		}

		/* MOUSE LOOK */
		double cursor_position_x;
		double cursor_position_y;
		// Aquire the current cursor position
		glfwGetCursorPos(glfw_window, &cursor_position_x, &cursor_position_y);

		// TODO - STORE Resolution of the camera

		// Calculate the offset from the screens centre this frame
		double delta_x = cursor_position_x - (1280 * 0.5);
		double delta_y = cursor_position_y - (720 * 0.5);
		// Move the cursor back to the centre of the render / window
		// TODO glfwSetInputMode(window , glfw_cursor_disabled)
		// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(glfw_window, 1280 * 0.5, 720 * 0.5);

		// If either input is non-zero, apply the rotation
		if (delta_x || delta_y)
		{
			// Identity matrix to accumulate rotation
			auto rotation = glm::mat4(1.0f);
			// Left / Right rotation
			rotation =  glm::rotate(rotation, float(angularSpeed * deltaTime * -delta_x), glm::vec3(viewTransform[1]));
			// Up / Down rotation
			rotation =  glm::rotate(rotation, float(angularSpeed * deltaTime * -delta_y), glm::vec3(1.0f, 0.0f, 0.0f));

			// Apply the rotation to the camera
			worldTransform *= rotation;
			// Update PxV
			updateProjectionViewTransform();
		}
}