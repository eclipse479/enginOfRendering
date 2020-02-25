#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "glm.hpp"
#include "fstream"
#include "sstream"
#include <crtdbg.h>
#include <iostream>

#include "OBJMesh.h"
#include "camera.h"
#include "flyingCamera.h"
#include "lightSource.h"
#include "mesh.h"
#include "shaders.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using uint = unsigned int;

struct light
{
	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	if(glfwInit() == false)
	return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	mesh theMesh;
	flyingCamera theFlyingCamera;
	shaders shaders;
	lightSource sun;
	aie::OBJMesh bunBun;
	light theLight;
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
	std::vector<Vertex> corners =
	{ //            ---position---        ---UV---         ---Normal---
		{glm::vec3(-0.5f, 0.5f, 0.5f),	 glm::vec2(0,0), glm::vec3(0,1,0)},     // top left       - 0
		{glm::vec3(0.5f, 0.5f, 0.5f),	 glm::vec2(1,0), glm::vec3(0,1,0)},     // top right      - 1
		{glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0,1), glm::vec3(0,1,0)},     // bottom left    - 2
		{glm::vec3(0.5f, -0.5f, 0.5f) ,  glm::vec2(1,1), glm::vec3(0,1,0)},     // bottom right   - 3 
		{glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec2(0,1), glm::vec3(0,1,0)},     // top left       - 4
		{glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec2(1,1), glm::vec3(0,1,0)},     // top right      - 5
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0,0), glm::vec3(0,1,0)},     // bottom left    - 6
		{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1,0), glm::vec3(0,1,0)}      // bottom right   - 7
	};

	std::vector<Vertex> sunVertex =
	{
		{glm::vec3(0.95f, 0.95f, 0.75f), glm::vec2(0,0), glm::vec3(0,0,1)},	    // 1
		{glm::vec3(0.75f, 0.95f, 0.75f), glm::vec2(0,0), glm::vec3(0,0,1)},     // 0
		{glm::vec3(0.75f, 0.75f, 0.75f), glm::vec2(0,0), glm::vec3(0,0,1)},	    // 2
		{glm::vec3(0.95f, 0.75f, 0.75f), glm::vec2(0,0), glm::vec3(0,0,1)},	    // 3 
		{glm::vec3(0.75f, 0.95f, 0.5f),	 glm::vec2(0,0), glm::vec3(0,0,1)},	    // 4
		{glm::vec3(0.95f, 0.95f, 0.5f),	 glm::vec2(0,0), glm::vec3(0,0,1)},	    // 5
		{glm::vec3(0.75f, 0.75f, 0.5f),	 glm::vec2(0,0), glm::vec3(0,0,1)},	    // 6
		{glm::vec3(0.95f, 0.75f, 0.5f),	 glm::vec2(0,0), glm::vec3(0,0,1)}      // 7 
	};
	int indexNumber = 6;
	std::vector<int> indexBuffer{
		2, 3, 6,
		3, 7, 6
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

	bunBun.load("..\\models\\Bunny.obj");
	
	/*----------------------send info to the GPU-------------------*/
	theMesh.meshSetUp(corners,indexBuffer);

    

	uint texture;
	int width, height, n;
	//finds the image
	unsigned char* data = stbi_load("..\\images\\Shrek.png", &width, &height, &n, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR SAMPLES texels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEARESTS RETURNS just closest pixel
	//sets the textures to mirrored repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//clears up memory

	stbi_image_free(data);

	uint texture2;
	int width2, height2, n2;
	//finds the image
	unsigned char* data2 = stbi_load("..\\images\\Bear_Blue_Base_Color.png", &width2, &height2, &n2, 0);
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR SAMPLES texels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEARESTS RETURNS just closest pixel
	//clears up memory
	stbi_image_free(	data2);

	//constructs the shaders
	shaders.createVertexShader("..\\shaders\\simple_vertex.glsl");

	shaders.createFragmentShader("..\\shaders\\simple_frag.glsl");
	
	shaders.linkShaderProgram();



	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 inverse = glm::mat4(1.0f);
	glPolygonMode(GL_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	///----------GAME LOOP----------///
	float currentFrame = 0;
	float lastFrame = 0;
	float deltaTime = 0;
	glfwSetCursorPos(window, 1280 * 0.5, 720 * 0.5);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0.5f,0,1.0f);
	//------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------
	glm::vec3 ambientLight = {0.25f,0.25f,0.25f};
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//manually creates delta time
		currentFrame = float(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
	   float time = glfwGetTime();

	   model = glm::mat4(1.0f);
	   theLight.direction = glm::normalize(glm::vec3(glm::cos(time*2), glm::sin(time*2), 0));
	   
	   glm::vec4 color = glm::vec4(sun.getColour(),1.0f);

	   auto uniformLocation = glGetUniformLocation(shaders.getShaderID(), "lightDirection");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(theLight.direction));

	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "projection_view_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(theFlyingCamera.getProjectionView()));

	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "model_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));
	  
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "normalMatrix");
	   glUniformMatrix3fv(uniformLocation, 1, false, glm::value_ptr(glm::inverseTranspose(glm::mat3(model))));

	   ////sets the colour for the polygons drawn
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "color");
	   glUniform4fv(uniformLocation, 1, glm::value_ptr(color));


	   theFlyingCamera.update(deltaTime);
	   glUseProgram(shaders.getShaderID());

	   //rotates the object
	   //model = glm::rotate(model, 0.016f, glm::vec3(0, 10, 0));

	   glBindTexture(GL_TEXTURE_2D, texture); // sets the texture to draw
	   theMesh.drawCube(indexNumber);// draws with texture set above
	   glBindTexture(GL_TEXTURE_2D, texture2);//sets new texture to draw
	   //bunBun.draw(false);//draws with new texture
	   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	   sun.drawLight(36);
	   
	   std::cout << time << "\n";
	   glfwSwapBuffers(window);
	   glfwPollEvents();
	}
	//------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------
	theMesh.~mesh();
	bunBun.~OBJMesh();
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &texture2);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
