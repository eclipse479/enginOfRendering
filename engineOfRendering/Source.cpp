#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
#include "fstream"
#include "sstream"

#include "camera.h"

using uint = unsigned int;
//test comment
int main()
{
	if(glfwInit() == false)
	return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	camera theCamera;
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
	int indexBuffer[]{ 0,1,2,1,3,2,4,5,6,5,7,6,0,2,4,4,2,6 };
	///create and load MESH

			///		Perspective(FieldOfView, ScreenAspectRatio, nearPoint, farPoint)
	
	///		lookAt(cameraPos, thingToLookAt, directionOfUp)
	glm::mat4 projection = theCamera.returnProjection();
	glm::mat4 view = theCamera.returnView();
	glm::mat4 model = theCamera.returnModel();

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 18 * sizeof(int), indexBuffer, GL_STATIC_DRAW);

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
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
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
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
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

		    theCamera.findDeltaTime();
			theCamera.update(window);

			projection = theCamera.returnProjection();
			view = theCamera.returnView();
		// our game logic and update code goes here!
		// so does our render code!
	   glm::mat4 pvm = projection * view * model;
	   static int frameCount = 0;
	   //view = glm::lookAt(glm::vec3(1.507f, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	   frameCount++;

	   glUseProgram(shaderProgramID);
	   
	   model = glm::rotate(model, 0.016f, glm::vec3(1, 0, 0));
	  glm::mat4 pv = projection * view;
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
	   auto uniformLocation = glGetUniformLocation(shaderProgramID, "projection_view_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(pv));

	   uniformLocation = glGetUniformLocation(shaderProgramID, "model_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));

	   uniformLocation = glGetUniformLocation(shaderProgramID, "color");
	   glUniform4fv(uniformLocation, 1, glm::value_ptr(color));

	   glBindVertexArray(VAO);
	   //glDrawArrays(GL_TRIANGLES, 0, 4);
	   glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT,0);


	   
	   
	   
	   
	   
	   glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1,&VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}