#pragma once
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 UV;
	glm::vec4 tangent;
};

class mesh
{
public:
	void meshSetUp(std::vector<Vertex> Vertex, std::vector<int> indexBuffer);

	~mesh();
	//returns certain values
	unsigned int getVAO();
	unsigned int getVBO();
	unsigned int getIBO();
	//draws plains based off of verticies given by using triangles
	void drawCube(int numberOfVerts);

private:
	//helps to send information to the buffers by storing the state needed to supply vertex data
	unsigned int VAO;
	//helps uploads information about the vertex (position, normal, UV) ect
	unsigned int VBO;
	// holds the order in which to draw the shapes vertices
	unsigned int IBO;
};

