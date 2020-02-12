#pragma once
#include "gl_core_4_5.h"
#include "fstream"
#include "sstream"

class shaders
{
public:
	void errorCheck(std::string shaderType);

	void createVertexShader();
	void createFragmentShader();
	void linkShaderProgram();
	unsigned int getShaderID();
private:
	std::string shaderData;

	std::stringstream stringStream;

	const char* data;

	unsigned int vertexShaderID = 0;
	unsigned int fragmentShaderID = 0;
	unsigned int shaderProgramID = 0;
};

