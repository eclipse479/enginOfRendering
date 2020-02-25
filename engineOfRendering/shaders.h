#pragma once
#include "gl_core_4_5.h"
#include "fstream"
#include "sstream"

class shaders
{
public:
	//gets the path to the vertex shader and sends it to the GPU
	void createVertexShader(std::string shaderType);
	//gets the path to the  fragment shader and sends it to the GPU
	void createFragmentShader(std::string shaderType); 
	//connect the vertex and fragment shader
	void linkShaderProgram();
	
	unsigned int getShaderID();
private:
	//makes sure thing work and displays error if it doesn't
	void printErrorLog(std::string shaderType);
	std::string shaderData;
	//ID's for the various shaders
	unsigned int vertexShaderID = 0;
	unsigned int fragmentShaderID = 0;
	//ID for the program
	unsigned int shaderProgramID = 0;
};

