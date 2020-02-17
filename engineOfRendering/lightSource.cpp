#include "lightSource.h"

lightSource::lightSource()
{
}

glm::vec3 lightSource::getColour()
{
	return cubeColour;
}

void lightSource::setColour(glm::vec3 newColour)
{
	cubeColour = newColour;
}

void lightSource::readyLight(glm::vec3 Vertecies[], int numberOfVerts, int indexBuffer[])
{
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glGenBuffers(1, &lightIBO);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), Vertecies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfVerts * sizeof(int), indexBuffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void lightSource::drawLight(int numberOfVerts)
{
	glBindVertexArray(lightVAO);
	glDrawElements(GL_TRIANGLES, numberOfVerts, GL_UNSIGNED_INT, 0);
}