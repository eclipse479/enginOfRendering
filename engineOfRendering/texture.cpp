#include "texture.h"

unsigned int texture::getTexture()
{
	return theDiffuseMap;
}


void texture::bind(const char *pathing)
{
	int program = -1;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	int diffuseTexUniform = glGetUniformLocation(program, "textureDiffuse");
	int normalTexUniform = glGetUniformLocation(program, "textureNormal");

	// Set textures to an ID
	if (diffuseTexUniform >= 0)
		glUniform1i(diffuseTexUniform, 0);
	if (normalTexUniform >= 0)
		glUniform1i(normalTexUniform, 1);

	// width of image, height of image, number of colour channels(RGBA) in image
	int width, height, n;
	//finds the image
	unsigned char* data = stbi_load(pathing, &width, &height, &n, 0);
	glGenTextures(1, &theDiffuseMap);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, theDiffuseMap);
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
	glDeleteTextures(1, &theDiffuseMap);
}

void texture::setNormalMap(unsigned int normalMap)
{
	theNormalMap = normalMap;

	
}

void texture::setTextureToDraw()
{
	// Get uniform ids
	int program = -1;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	int diffuseTexUniform = glGetUniformLocation(program, "textureDiffuse");
	int normalTexUniform = glGetUniformLocation(program, "textureNormal");

	// Set textures to an ID
	if (diffuseTexUniform >= 0)
		glUniform1i(diffuseTexUniform, 0);
	// Set textures to an ID
	if (normalTexUniform >= 0)
		glUniform1i(normalTexUniform, 1);
	//binds the diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, theDiffuseMap);//binds the next texture to draw
	//binds the normal map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, theNormalMap);//binds the next texture to draw
}