#include "mesh.h"

mesh::mesh()
{

}

mesh::~mesh()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void mesh::meshSetUp(Vertecies Vertecies[], int numberOfVerts, int indexBuffer[])
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), Vertecies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfVerts * sizeof(int), indexBuffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));

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