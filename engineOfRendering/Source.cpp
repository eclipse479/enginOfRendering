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
#include "mesh.h"
#include "shaders.h"
#include "texture.h"
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
	//creates the objects that are used
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	mesh theMesh;
	flyingCamera theFlyingCamera;
	shaders shaders;
	aie::OBJMesh swoleBear;
	aie::OBJMesh swordShield;
	light theLight;
	light theSun;

	texture swoleBearDiffuse;
	texture shieldDiffuse;
	texture shieldNormal;
	texture swordDiffuse;
	texture swordNormal;

	
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}
	//create the window
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
		{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec3(0,1,0), glm::vec2(0,0) },		// top left       - 0
		{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec3(0,1,0), glm::vec2(1,0) },		// top right      - 1
		{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0,1,0), glm::vec2(0,1) },		// bottom left    - 2
		{glm::vec3(0.5f, -0.5f, 0.5f) , glm::vec3(0,1,0), glm::vec2(1,1) },		// bottom right   - 3 
		{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0,1,0), glm::vec2(0,1) },		// top left       - 4
		{glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec3(0,1,0), glm::vec2(1,1) },		// top right      - 5
		{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec3(0,1,0), glm::vec2(0,0) },		// bottom left    - 6
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0,1,0), glm::vec2(1,0) }		// bottom right   - 7
	};

	int indexNumber = 6;
	std::vector<int> indexBuffer{
		2, 3, 6,
		3, 7, 6
	};
	
	///create and load MESH
	swoleBear.load("..\\models\\swoleBear.obj");
	swordShield.load("..\\models\\meshSwordShield.obj");
	
	/*----------------------send info to the GPU-------------------*/
	//loads the square
	theMesh.meshSetUp(corners,indexBuffer);

    //binds the textures
	swoleBearDiffuse.bind("..\\images\\yellowBear.png");
	stbi_set_flip_vertically_on_load(true);
	shieldDiffuse.bind("..\\images\\shieldTexture.png");
	shieldNormal.bind("..\\images\\shieldNormal.png");
	swordDiffuse.bind("..\\images\\swordDiffuse.png");
	swordNormal.bind("..\\images\\swordNormal.png");
	//constructs the shaders
	shaders.createVertexShader("..\\shaders\\simple_vertex.glsl");

	shaders.createFragmentShader("..\\shaders\\simple_frag.glsl");
	//link the two shaders together
	shaders.linkShaderProgram();

	shieldDiffuse.setNormalMap(shieldNormal.getTexture());
	swordDiffuse.setNormalMap(swordNormal.getTexture());
	//set the model matrix
	glm::mat4 model = glm::mat4(1.0f);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	float currentFrame = 0;
	float lastFrame = 0;
	float deltaTime = 0;

	glfwSetCursorPos(window, 1280 * 0.5, 720 * 0.5);// moves the cursor to the center of the window
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // turns the cursor off
	glEnable(GL_DEPTH_TEST);// turns on depth test
	glClearColor(0,0,0.2f,1);
	//------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------
	//light # 1
	theLight.diffuse = glm::vec3(0.75f, 0, 0);
	theLight.specular = glm::vec3(1, 0, 0);
	//light # 2
	theSun.diffuse = glm::vec3(0, 0, 0.75f);
	theSun.specular = glm::vec3(0, 0, 1);
	//global ambient light(no direct lighting)
	glm::vec3 ambientLight = {0.5f,0.5f,0.5f};
	///----------GAME LOOP----------///
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//----- manually creates delta time -----
		currentFrame = float(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//----------------------------------------

	   //rotates the world
	  // model = glm::rotate(model, 0.016f, glm::vec3(0, 1, 0));

	   //allows camera movement
	   theFlyingCamera.update(deltaTime);
	   glUseProgram(shaders.getShaderID());

	   //changes the light direction based on the current time
	   float time = glfwGetTime();
	   theLight.direction = glm::normalize(glm::vec3(glm::cos(time*2), glm::sin(time*2), 0));
	   theSun.direction = glm::normalize(glm::vec3(glm::cos(-time * 2), glm::sin(-time * 2), 0));
	 
	   //---------------sets the uniforms in the shader programs---------------
	   //moving light
	   auto uniformLocation = glGetUniformLocation(shaders.getShaderID(), "lightDirection");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(theLight.direction));

	   //sets the projection veiw matrix in the shader
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "projection_view_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(theFlyingCamera.getProjectionView()));

	   //sets the normal matric in the shader
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "normalMatrix");
	   glUniformMatrix3fv(uniformLocation, 1, false, glm::value_ptr(glm::inverseTranspose(glm::mat3(model))));

	   //sets the light settings for the first light in the shader (red)
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "ambientLight");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(ambientLight));
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "diffuseLight");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(theLight.diffuse));
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "specularLight");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(theLight.specular));

	   //material colours that the shader uses for the object
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "Ka");//material ambience
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(glm::vec3(0.4f)));
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "Kd");//material diffuse
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(glm::vec3(0,.80f,0.9f)));
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "Ks");//material specular
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(glm::vec3(0.4f)));

	   //the light statistics for the second light (blue)
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "lightDirectionSun");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(theSun.direction));
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "ambientLightSun");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(ambientLight));
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "diffuseLightSun");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(theSun.diffuse));
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "specularLightSun");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(theSun.specular));

	   //the position of the camera is sent to the shader to calculate specular light 
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "cameraPosition");
	   glUniform3fv(uniformLocation, 1, glm::value_ptr(theFlyingCamera.getPosition()));

	   //sends the model matrix to the shader
	   uniformLocation = glGetUniformLocation(shaders.getShaderID(), "model_matrix");
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));
	   


	   //glBindTexture(GL_TEXTURE_2D, texture2); // sets the texture to draw
	   //move objects position
	   model[3] = glm::vec4(0,0,0,1);
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));
	  // swoleBear.draw(false);//draws with new texture

	   shieldDiffuse.setTextureToDraw();//sets new texture to draw
	   model[3] = glm::vec4(0, 0, 8, 1);
	   //move objects position
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));
	   //swordShield.draw(false);//draws with new texture
	   aie::OBJMesh::draw(swordShield.getChunks()[0]);
	   //draw sword
	   swordDiffuse.setTextureToDraw();
	   aie::OBJMesh::draw(swordShield.getChunks()[1]);
	   model[3] = glm::vec4(0, -3, 0, 1);
	   glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));
	   theMesh.drawCube(indexNumber);// draws with texture set above
	   glPolygonMode(GL_BACK, GL_LINE);
	   
	   
	   glfwSwapBuffers(window);
	   glfwPollEvents();
	}
	//------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------
	//clearing space/deleting everything
	theMesh.~mesh();
	//swoleBear.~OBJMesh();
	swordShield.~OBJMesh();
	swoleBearDiffuse.deleteTexture();
	shieldDiffuse.deleteTexture();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
