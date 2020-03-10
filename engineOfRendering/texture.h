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
	void setTextureToDraw();


private:
	//size of the texture
	float width;
	float height;
	float n;

	//holds the texture
	unsigned char* data;
	unsigned int theTexture;
};

