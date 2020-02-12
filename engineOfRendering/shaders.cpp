#include "shaders.h"

void shaders::createVertexShader()
{
	std::ifstream inFileStream("..\\shaders\\simple_vertex.glsl", std::ifstream::in);

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

	
}

void shaders::createFragmentShader()
{
	std::ifstream fragInFileStream("..\\shaders\\simple_frag.glsl", std::ifstream::in);
	std::stringstream fragStringStream;
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
}
void shaders::errorCheck(std::string shaderType)
{
	//did it work?
	GLint success = GL_FALSE;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//get length of open GL error message
		GLint logLength = 0;
		glGetShaderiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
		//create new error buffer
		char* log = new char[logLength];
		//copy the error into the buffer
		glGetProgramInfoLog(shaderProgramID, logLength, 0, log);
		//create error message
		std::string errorMessage(log);
		errorMessage += (shaderType + "failed to compile");
		printf(errorMessage.c_str());
		//clean up
		delete[] log;
	}
}


unsigned int shaders::getShaderID()
{
	return shaderProgramID;
}