#pragma once
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 UV;
	glm::vec3 normal;
};

class mesh
{
public:
	void meshSetUp(std::vector<Vertex> Vertex, std::vector<int> indexBuffer);

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

