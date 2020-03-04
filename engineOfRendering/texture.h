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
	float width;
	float height;
	float n;

	unsigned char* data;
	unsigned int theTexture;
};

