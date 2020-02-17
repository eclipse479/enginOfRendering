#include "lightSource.h"

lightSource::lightSource()
{
}

glm::vec3 lightSource::getColour()
{
	return fragColour;
}

void lightSource::setColour(glm::vec3 newColour)
{
	cubeColour = newColour;
}