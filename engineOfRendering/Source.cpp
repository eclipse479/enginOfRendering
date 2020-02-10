#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
#include "fstream"
#include "sstream"

#include "camera.h"
#include "flyingCamera.h"

using uint = unsigned int;

int main()
{
	if(glfwInit() == false)
	return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	flyingCamera theFlyingCamera;
	//camera theCamera;
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
		glm::vec3(-0.5f, 0.5f, 0.0),		  // 0
		glm::vec3(0.5f, 0.5f, 0.0),			  // 1
		glm::vec3(-0.5f, -0.5f, 0.0),		 // 2
		glm::vec3(0.5f, -0.5f, 0.0),		 // 3 
		glm::vec3(-0.5f, 0.5f, -0.5),    // 4
		glm::vec3(0.5f, 0.5f, -0.5),     // 5
		glm::vec3(-0.5f, -0.5f, -0.5),  // 6
		glm::vec3(0.5f, -0.5f, -0.5)    // 7
	};
	//int numberOfVerts = 6;
	int indexBuffer[]{ 0,1,2,1,3,2,4,6,5,5,6,7,0,2,4,4,2,6,1,5,3,5,7,3 };
	///create and load MESH

			///		Perspective(FieldOfView, ScreenAspectRatio, nearPoint, farPoint)
	
	///		lookAt(cameraPos, thingToLookAt, directionOfUp)
	glm::mat4 model = glm::mat4(0.0f);

	/*send info to the GPU-------------------*/
	uint VAO;
	uint VBO;
	uint IBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), Vertecies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(int), indexBuffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
	bool up = true;
	float sinNumber = 0;
	float cosNumber = 0;
	float number = 0;

	float currentFrame = 0;
	float lastFrame = 0;
	float deltaTime = 0;
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{

		//manually creates delta time
		currentFrame = float(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
		{
			glClearColor(0.5, 1.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			glClearColor(0.0, 1.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			glClearColor(1.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		else
		{
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		theFlyingCamera.update(deltaTime);
	   
	   static int frameCount = 0;
	   //view = glm::lookAt(glm::vec3(1.507f, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	   frameCount++;


	   glUseProgram(shaderProgramID);
	   //rotates the object
	   model = glm::rotate(model, 0.016f, glm::vec3(1, 0, 0));

	  //for colour changing properties
	  sinNumber = sin(number);
	  cosNumber = cos(number);
	  if (sinNumber < 0)
	  {
		  sinNumber = -sinNumber;
	  }
	  if (cosNumber < 0)
	  {
		  cosNumber = -cosNumber;
	  }
	   glm::vec4 color = glm::vec4(sinNumber, cosNumber, sin(number),1.0f);
	   number += 0.03f;
	   //----------END COLOUR CHANGING PROPERTIES-------------------------
	   auto uniformLocation = glGetUniformLocation(shaderProgramID, "projection_view_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(theFlyingCamera.getProjectionView()));

	   uniformLocation = glGetUniformLocation(shaderProgramID, "model_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));

	   //sets the colour for the polygons drawn
	   uniformLocation = glGetUniformLocation(shaderProgramID, "color");
	   glUniform4fv(uniformLocation, 1, glm::value_ptr(color));

	   glBindVertexArray(VAO);
	   //glDrawArrays(GL_TRIANGLES, 0, 4);
	   glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT,0);
	   
	   glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1,&VAO);
	glDeleteBuffers(1, &VBO);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
