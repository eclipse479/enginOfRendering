#pragma once
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
class mesh
{
public:
	void meshSetUp(glm::vec3 Vertecies[], int numberOfVerts, int indexBuffer[]);

	mesh();
	~mesh();

	unsigned int getVAO();
	unsigned int getVBO();
	unsigned int getIBO();

	void drawCube(int numberOfVerts);

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;
};

