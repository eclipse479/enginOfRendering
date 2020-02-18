#pragma once
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"

struct Vertecies
{
	glm::vec3 position;
	glm::vec2 UV;
};

class mesh
{
public:
	void meshSetUp(Vertecies Vertex[], int numberOfVerts, int indexBuffer[]);

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

