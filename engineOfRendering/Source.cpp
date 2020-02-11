#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
#include "fstream"
#include "sstream"

#include "camera.h"
#include "flyingCamera.h"
#include "lightSource.h"
#include "mesh.h"

using uint = unsigned int;

int main()
{
	if(glfwInit() == false)
	return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	mesh theMesh;
	flyingCamera theFlyingCamera;

	lightSource theLight;
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);
	//code goes here
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{ 
		glfwDestroyWindow(window); 
		glfwTerminate(); 
		return -3; 
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	printf("GL: %i.%i\n", major, minor);
	//mesh data
	glm::vec3 Vertecies[] =
	{
		glm::vec3(-0.5f, 0.5f, 0.5),		  // 0
		glm::vec3(0.5f, 0.5f, 0.5),			  // 1
		glm::vec3(-0.5f, -0.5f, 0.5),		 // 2
		glm::vec3(0.5f, -0.5f, 0.5),		 // 3 
		glm::vec3(-0.5f, 0.5f, -0.5),    // 4
		glm::vec3(0.5f, 0.5f, -0.5),     // 5
		glm::vec3(-0.5f, -0.5f, -0.5),  // 6
		glm::vec3(0.5f, -0.5f, -0.5),    // 7

		glm::vec3(0.75f, 0.5f, 0.5),		  // 8
		glm::vec3(0.9f, 0.5f, 0.5),			  // 9
		glm::vec3(0.75f, 0.2f, 0.5),		 // 10
		glm::vec3(0.9f, 0.3f, 0.5)		 // 11
	};
	int numberOfVerts = 42;
	int indexBuffer[]{
		0,1,2,
		1,3,2,
		4,6,5,
		5,6,7,
		0,2,4,
		4,2,6,
		1,5,3,
		5,7,3,
		0,4,1,
		4,5,1,
		2,3,6,
		3,7,6,
		8,9,10,
		9,11,10
	};
	///create and load MESH

	glm::mat4 model = glm::mat4(1.0f);

	/*send info to the GPU-------------------*/
	theMesh.meshSetUp(Vertecies,numberOfVerts,indexBuffer);
    //--------------------------------------


	uint vertexShaderID = 0;
	uint fragmentShaderID = 0;
	uint shaderProgramID = 0;


	std::string shaderData;
	std::ifstream inFileStream("..\\shaders\\simple_vertex.glsl", std::ifstream::in);
	std::stringstream stringStream;
	if (inFileStream.is_open())
	{
		stringStream << inFileStream.rdbuf();
		shaderData = stringStream.str();
		inFileStream.close();
	}
	//allocate space for shader program
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//convert to raw char*
	const char* data = shaderData.c_str();
	//send in the char* to shader location
	glShaderSource(vertexShaderID, 1, (const GLchar**)&data, 0);
	//build
	glCompileShader(vertexShaderID);

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
		glGetShaderInfoLog(shaderProgramID, logLength, 0, log);
		//create error message
		std::string errorMessage(log);
		errorMessage += "Vertex failed to compile";
		printf(errorMessage.c_str());
		//clean up
		delete[] log;
	}

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

	//did it work?
	success = GL_FALSE;
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//get length of open GL error message
		GLint logLength = 0;
		glGetShaderiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
		//create new error buffer
		char* log = new char[logLength];
		//copy the error into the buffer
		glGetShaderInfoLog(shaderProgramID, logLength, 0, log);
		//create error message
		std::string errorMessage(log);
		errorMessage += "fragment failed to compile";
		printf(errorMessage.c_str());
		//clean up
		delete[] log;
	}

	//create shader program
	shaderProgramID = glCreateProgram();
	//attach both shaders by ID and type
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);

	//link both programs
	glLinkProgram(shaderProgramID);
	success = GL_FALSE;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
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
		errorMessage += "Linking failed to compile";
		printf(errorMessage.c_str());
		//clean up
		delete[] log;
	}

	glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	///----------GAME LOOP----------///
	float currentFrame = 0;
	float lastFrame = 0;
	float deltaTime = 0;
	glfwSetCursorPos(window, 1280 * 0.5, 720 * 0.5);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//manually creates delta time
		currentFrame = float(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	
		theFlyingCamera.update(deltaTime);
	   
	 
	   glUseProgram(shaderProgramID);
	   //rotates the object
	   model = glm::rotate(model, 0.016f, glm::vec3(1, 0, 0));

	  //for colour changing properties
		if (glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			theLight.setColour(glm::vec3(0.0f, 1.0f, 0.5f));
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		}
	   glm::vec4 color = glm::vec4(theLight.getColour(),1.0f);
	   //----------END COLOUR CHANGING PROPERTIES-------------------------

	   auto uniformLocation = glGetUniformLocation(shaderProgramID, "projection_view_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(theFlyingCamera.getProjectionView()));

	   uniformLocation = glGetUniformLocation(shaderProgramID, "model_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));

	   //sets the colour for the polygons drawn
	   uniformLocation = glGetUniformLocation(shaderProgramID, "color");
	   glUniform4fv(uniformLocation, 1, glm::value_ptr(color));

	   glBindVertexArray(theMesh.getVAO());
	   //glDrawArrays(GL_TRIANGLES, 0, 4);
	   theMesh.drawCube(numberOfVerts);
	   
	   glfwSwapBuffers(window);
		glfwPollEvents();
	}

	theMesh.~mesh();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
