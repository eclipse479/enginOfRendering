#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
#include "fstream"
#include "sstream"

#include "OBJMesh.h"
#include "camera.h"
#include "flyingCamera.h"
#include "lightSource.h"
#include "mesh.h"
#include "shaders.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using uint = unsigned int;

int main()
{
	if(glfwInit() == false)
	return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	mesh theMesh;
	flyingCamera theFlyingCamera;
	shaders shaders;
	lightSource theLight;
	lightSource sun;
	//aie::OBJMesh swoleBear;
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
	Vertecies Vertex[] =
	{ //            ---position---                          ---UV---
		glm::vec3(-0.5f, 0.5f, 0.5f),	       glm::vec2 (0,0),  // 0
		glm::vec3(0.5f, 0.5f, 0.5f),	   	   glm::vec2 (1,0), // 1
		glm::vec3(-0.5f, -0.5f, 0.5f),       glm::vec2 (0,1),// 2
		glm::vec3(0.5f, -0.5f, 0.5f),    	   glm::vec2 (1,1), // 3 
		glm::vec3(-0.5f, 0.5f, -0.5f),       glm::vec2 (0,1),   // 4
		glm::vec3(0.5f, 0.5f, -0.5f),        glm::vec2 (1,1),   // 5
		glm::vec3(-0.5f, -0.5f, -0.5f),     glm::vec2 (0,0),// 6
		glm::vec3(0.5f, -0.5f, -0.5f),       glm::vec2 (1,0)   // 7
	};

	Vertecies sunVertex[] =
	{
		glm::vec3(0.75f, 0.95f, 0.75f),	glm::vec2(0,0),	  // 0
		glm::vec3(0.95f, 0.95f, 0.75f),	glm::vec2(0,0),	  // 1
		glm::vec3(0.75f, 0.75f, 0.75f),	glm::vec2(0,0),	 // 2
		glm::vec3(0.95f, 0.75f, 0.75f),	glm::vec2(0,0),	 // 3 
		glm::vec3(0.75f, 0.95f, 0.5f),	glm::vec2(0,0),	  // 4
		glm::vec3(0.95f, 0.95f, 0.5f),	glm::vec2(0,0),	  // 5
		glm::vec3(0.75f, 0.75f, 0.5f),	glm::vec2(0,0),	 // 6
		glm::vec3(0.95f, 0.75f, 0.5f),	glm::vec2(0,0) 	 // 7 
	};
	int numberOfVerts = 6;
	int indexBuffer[]{
		0, 1, 2,
		1, 3, 2
		/*4, 6, 5,
		5, 6, 7,
		0, 2, 4,
		4, 2, 6,
		1, 5, 3,
		5, 7, 3,
		0, 4, 1,
		4, 5, 1,
		2, 3, 6,
		3, 7, 6,*/
	};
	///create and load MESH
	glm::mat4 model = glm::mat4(1.0f);
	//swoleBear.load("..\\models\\swoleBear.obj");
	/*----------------------send info to the GPU-------------------*/
	theMesh.meshSetUp(Vertex,numberOfVerts,indexBuffer);

    

	uint texture;
	int width, height, n;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	unsigned char* data = stbi_load("..\\images\\Shrek.jpg", &width, &height, &n, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR SAMPLES texels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEARESTS RETURNS just closest pixel
	stbi_image_free(	data);

	shaders.createVertexShader("..\\shaders\\simple_vertex.glsl");

	shaders.createFragmentShader("..\\shaders\\simple_frag.glsl");

	shaders.linkShaderProgram();




	glPolygonMode(GL_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	///----------GAME LOOP----------///
	float currentFrame = 0;
	float lastFrame = 0;
	float deltaTime = 0;
	glfwSetCursorPos(window, 1280 * 0.5, 720 * 0.5);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glClearColor(1.0f,1.0f,1.0f,1.0f);
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//manually creates delta time
		currentFrame = float(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	
		theFlyingCamera.update(deltaTime);
	   
	 
	   glUseProgram(shaders.getShaderID());
	   //rotates the object
	   //model = glm::rotate(model, 0.016f, glm::vec3(0, 10, 0));

	  //for colour changing properties
		if (glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			theLight.setColour(glm::vec3(0.0f, 1.0f, 0.5f));
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		}
	   glm::vec4 color = glm::vec4(theLight.getColour(),1.0f);
	   //--------------------END COLOUR CHANGING PROPERTIES-------------------------


	   auto uniformLocation = glGetUniformLocation(shaders.getShaderID(), "objectColor");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(glm::vec3(0.75f, 0.0f, 0.75f)));
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "lightColor");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(glm::vec3(1.0f)));

	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "projection_view_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(theFlyingCamera.getProjectionView()));

	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "model_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));

	   //sets the colour for the polygons drawn
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "color");
	   glUniform4fv(uniformLocation, 1, glm::value_ptr(color));

	   glBindTexture(GL_TEXTURE_2D, texture);

	   theMesh.drawCube(numberOfVerts);
	   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	   //swoleBear.draw(false);
	   glPolygonMode(GL_BACK, GL_FILL);
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "objectColor");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.5f)));
	   sun.drawLight(36);
	   
	   glfwSwapBuffers(window);
		glfwPollEvents();
	}

	theMesh.~mesh();
	//swoleBear.~OBJMesh();
	glDeleteTextures(1, &texture);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
