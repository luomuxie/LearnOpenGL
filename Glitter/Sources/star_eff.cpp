#include "star_eff.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "func.h"
#include <shader_s.h>
#include "Constants.h"

void StarEff::initOpenGL()
{
	//init glfw
	glfwInit();
	//set opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set opengl profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window to be resizable
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//create window 
	window = glfwCreateWindow(width, height, "Star Effect", NULL, NULL);
	//check if window is created
	if (window == NULL)
	{
		//if window is not created
		//print error message
		std::cout << "Failed to create GLFW window" << std::endl;
		//terminate glfw
		glfwTerminate();
		//return -1
		return;
	}

	//make the window current
	glfwMakeContextCurrent(window);

	//init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//if glad is not loaded
		//print error message
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1
		return;
	}

	//set the viewport
	glViewport(0, 0, width, height);
		
}

void StarEff::initVertex()
{
	//create a plane vertex with 4 vertices
	float plane[] = {
		//position				
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f
	};

	//set the vao and vbo
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	//bind the vao and vbo
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//set the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);
	//set the vertex attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	//enable the vertex attribute pointer
	glEnableVertexAttribArray(0);

	//unbind the vao and vbo
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void StarEff::run()
{
	//init opengl
	initOpenGL();
	//init vertex
	initVertex();
	//init shader for shader Class
	Shader shader((SHADER_PATH + "star_eff.vs").c_str(), (SHADER_PATH + "star_eff.fs").c_str());

	//create main loop
	while (!glfwWindowShouldClose(window))
	{
		//process input
		processInput(window);

		//set the background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//use the shader
		shader.use();

		//set the time
		float time = glfwGetTime();
		//set the time to the shader
		shader.setFloat("iTime", time);

		//create a vec2 for the resolution
		glm::vec2 resolution = glm::vec2(width, height);

		//set the resolution
		shader.setVec2("iResolution", resolution);		

		//bind the vao
		glBindVertexArray(vao);
		//draw the plane
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//unbind the vao
		glBindVertexArray(0);
		
		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}

}


