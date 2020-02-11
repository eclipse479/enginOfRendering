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