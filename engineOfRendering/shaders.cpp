#include "shaders.h"

void shaders::createVertexShader(std::string shaderPath)
{
	std::ifstream inFileStream(shaderPath, std::ifstream::in);
	std::stringstream stringStream;
	const char* data;
	if (inFileStream.is_open())
	{
		stringStream << inFileStream.rdbuf();
		shaderData = stringStream.str();
		inFileStream.close();
	}
	//allocate space for shader program
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//convert to raw char*
	data = shaderData.c_str();
	//send in the char* to shader location
	glShaderSource(vertexShaderID, 1, (const GLchar**)&data, 0);
	//build
	glCompileShader(vertexShaderID);
	GLint success = GL_FALSE;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		printErrorLog("Vertex");
	}
}

void shaders::createFragmentShader(std::string shaderPath)
{
	std::ifstream fragInFileStream(shaderPath, std::ifstream::in);
	std::stringstream fragStringStream;
	const char* data;
	if (fragInFileStream.is_open())
	{
		fragStringStream << fragInFileStream.rdbuf();
		shaderData = fragStringStream.str();
		fragInFileStream.close();
	}
	//allocate space for shader program
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	//convert to raw char*
	data = shaderData.c_str();
	//send in the char* to shader location
	glShaderSource(fragmentShaderID, 1, (const GLchar**)&data, 0);
	//build
	glCompileShader(fragmentShaderID);
	GLint success = GL_FALSE;
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		printErrorLog("Fragment");
	}
}

void shaders::linkShaderProgram()
{
	//create shader program
	shaderProgramID = glCreateProgram();
	//attach both shaders by ID and type
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	//link both programs
	glLinkProgram(shaderProgramID);

	//check compile status
	GLint logLength = 0;
	glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
	char* log = new char[logLength];

	GLint success = 0;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		printErrorLog("Linking");
	}
}

void shaders::printErrorLog(std::string shaderType)
{
		//get length of open GL error message
		GLint logLength = 0;
		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
		//create new error buffer
		char* log = new char[logLength];
		glGetProgramInfoLog(shaderProgramID, logLength, 0, log);
		//copy the error into the buffer
		//create error message
		std::string errorMessage(log);
		errorMessage += (shaderType + " failed to compile");
		printf(errorMessage.c_str());
		//clean up
		delete[] log;
}


unsigned int shaders::getShaderID()
{
	return shaderProgramID;
}