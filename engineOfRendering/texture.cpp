#include "texture.h"

unsigned int texture::getTexture()
{
	return theTexture;
}


void texture::bind(const char *pathing)
{
	// width of image, height of image, number of colour channels(RGBA) in image
	int width, height, n;
	//finds the image
	unsigned char* data = stbi_load(pathing, &width, &height, &n, 0);
	glGenTextures(1, &theTexture);
	glBindTexture(GL_TEXTURE_2D, theTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR SAMPLES texels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEARESTS RETURNS just closest pixel
	//sets the textures to mirrored repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//clears up memory
	stbi_image_free(data);
}

void texture::deleteTexture()
{
	//removes the texture
	glDeleteTextures(1, &theTexture);
}

void texture::setTextureToDraw()
{
	glBindTexture(GL_TEXTURE_2D, theTexture);//binds the next texture to draw
}