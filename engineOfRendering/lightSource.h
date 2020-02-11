#pragma once
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"


class lightSource
{
public:
	lightSource();

	glm::vec3 getColour();
	void setColour(glm::vec3 newColour);
private:
	glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 cubeColour = glm::vec3(0.5f, 0.0f, 0.5f);
	glm::vec3 result = lightColour * cubeColour;
};

