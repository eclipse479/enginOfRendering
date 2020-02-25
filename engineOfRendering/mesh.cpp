#include "mesh.h"


mesh::~mesh()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void mesh::meshSetUp(std::vector<Vertex> Vertecies, std::vector<int> indexBuffer)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, /*number or vertecies used*/ Vertecies.size() * sizeof(Vertex) , &Vertecies[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(int), &indexBuffer[0], GL_STATIC_DRAW);
	
	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3* sizeof(float)));

	//enable third element as normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(5 * sizeof(float)));


	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	
}

unsigned int mesh::getVAO()
{
	return VAO;
}
unsigned int mesh::getVBO()
{
	return VBO;
}
unsigned int mesh::getIBO()
{
	return IBO;
}

void mesh::drawCube(int numberOfVerts)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numberOfVerts, GL_UNSIGNED_INT, 0);
}