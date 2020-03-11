#pragma once
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
#include "stb_image.h"
class texture
{
public:
	
	unsigned int getTexture();
	void bind(const char* pathing);
	void deleteTexture();
	//set another texture as a normal map (used to combine teh diffuse and normal maps)
	void setNormalMap(unsigned int normalMap);
	//sets the texture that the engine will draw next
	void setTextureToDraw();


private:
	//size of the texture
	float width;
	float height;
	float n;

	//holds the texture
	unsigned char* data;
	unsigned int theDiffuseMap;
	unsigned int theNormalMap;
};

