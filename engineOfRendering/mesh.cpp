#include "mesh.h"


mesh::~mesh()
{
	//delets the buffers
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void mesh::meshSetUp(std::vector<Vertex> Vertecies, std::vector<int> indexBuffer)
{
	//generates buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	//binds buffers
	//binds the VAO
	glBindVertexArray(VAO);
	//binds the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertecies.size() * sizeof(Vertex) , &Vertecies[0], GL_STATIC_DRAW);
	//binds the IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(int), &indexBuffer[0], GL_STATIC_DRAW);
	
	//enables the first element of the struct (position)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//enables the second element of the struct (normal)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	// enables the third element of the struct (UV)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6* sizeof(float)));


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
	//draws points when verticies are given
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numberOfVerts, GL_UNSIGNED_INT, 0);
}