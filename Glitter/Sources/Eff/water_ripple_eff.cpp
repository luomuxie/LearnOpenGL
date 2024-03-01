#include "water_ripple_eff.h"
#include <glad/glad.h>
#include <iostream>
#include <shader_s.h>
#include "../func.h"
#include <Constants.h>


void water_ripple_eff::initOpengl()
{
	//init glfw
	glfwInit();
	//set opengl version 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set opengl profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window can be resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(width, height, "water_ripple_eff", nullptr, nullptr);

	//check the window is created or not
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	//set the window to the current context
	glfwMakeContextCurrent(window);

	//init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
	}

	//set the size of the viewport
	glViewport(0, 0, width, height);
}

void water_ripple_eff::initVertex()
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

void water_ripple_eff::run()
{
	//init opengl
	initOpengl();
	initVertex();

	//create a shader
	Shader shader((SHADER_Eff_PATH + "water_ripple_eff.vs").c_str(), (SHADER_Eff_PATH + "water_ripple_eff.fs").c_str());
	//load a texture;
	unsigned int texture = loadTexture((TEXTURE_PATH + "mossy_pebbles.png").c_str());
	//set the texture
	shader.use();
	shader.setInt("ourTexture", 0);
	

	//set the render loop
	while (!glfwWindowShouldClose(window))
	{
		//set the input
		processInput(window);

		//set the background color
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		//clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////set the shader
		shader.use();

		////set the time
		float time = glfwGetTime();
		shader.setFloat("iTime", time);

		//set the iResolution
		shader.setVec2("iResolution", glm::vec2(width, height));

		//get the mouse position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		//set the mouse position 
		shader.setVec2("iMouse", glm::vec2(xpos, ypos));

		

		//set the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		//bind the vao 
		glBindVertexArray(vao);
		//draw the plane
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);	

		//swap the buffer
		glfwSwapBuffers(window);

		//poll the event
		glfwPollEvents();
	}

	//clear the window
	glfwTerminate();
}
