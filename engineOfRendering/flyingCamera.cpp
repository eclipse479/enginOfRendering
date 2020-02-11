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

		//LEFT
		displacement.x -= glfwGetKey(glfw_window, GLFW_KEY_A);
		//RIGHT
		displacement.x += glfwGetKey(glfw_window, GLFW_KEY_D);
		//FORWARDS
		displacement.z += glfwGetKey(glfw_window, GLFW_KEY_W);
		//BACKWARDS
		displacement.z -= glfwGetKey(glfw_window, GLFW_KEY_S);
		//DOWN
		displacement.y += glfwGetKey(glfw_window, GLFW_KEY_Q);
		//UP
		displacement.y -= glfwGetKey(glfw_window, GLFW_KEY_E);
		//moves the camera in the direction the camera is facing
		
		glm::vec4 moveDirection = -displacement.z * worldTransform[2] + displacement.x * worldTransform[0] + displacement.y * worldTransform[1];
		glm::normalize(moveDirection);

	    this->worldTransform[3] += (moveDirection * speed * deltaTime);
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