
#include "instancing_quads.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "Constants.h"
#include "func.h"
#include <glm/ext/vector_float2.hpp>
#include <shader_s.h>

void instancing_quads::initOpenGL()
{
	//init glwf
	glfwInit();
	//set opengl version for 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//set opengl core
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//enable the resize window
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "instancing_quads", NULL, NULL);
	//glfwSetWindowPos(window, 0, 1000 - SCR_HEIGHT);


	//check the window is null
	if (window == NULL)
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

	
	//set the view size
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);			
}



void instancing_quads::initVertex()
{

	// generate a list of 100 quad locations/translation-vectors
	// ---------------------------------------------------------


	glm::vec2 translations[100];
	int index = 0;
	float spacing = 0.2f; // spacing between quads
	int num_quads_per_row = 10;
	float start_offset = (num_quads_per_row / 2) * spacing - spacing / 2; // to center the grid of quads

	for (int y = 0; y < num_quads_per_row; y++)
	{
		for (int x = 0; x < num_quads_per_row; x++)
		{
			glm::vec2 translation;
			translation.x = (x * spacing) - start_offset;
			translation.y = (y * spacing) - start_offset;
			translations[index++] = translation;
		}
	}
	

	////print the translations
	//for (int i = 0; i < 100; i++)
	//{
	//	std::cout << translations[i].x << " " << translations[i].y << std::endl;
	//}

	//store the instance data in an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	float quadVertices[] = {
		// positions     // colors
		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
	};

	//set vao and vbo 
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	//bind the vao and vbo
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

	//set the vbo data
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	//set the vertex attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//enable the vertex attribute array
	glEnableVertexAttribArray(0);

	//set the vertex color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	//enable the vertex color attribute array
	glEnableVertexAttribArray(1);

	//set the instance data attribute pointer
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);	
	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.


	//unbind the vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

void instancing_quads::run()
{
	initOpenGL();

	initVertex();

	//init shader by shader class 
	Shader shader((SHADER_PATH + "instancing.vs").c_str(), (SHADER_PATH + "instancing.fs").c_str());

	//open deth test
	//glEnable(GL_DEPTH_TEST);
	
	//main loop 
	while (!glfwWindowShouldClose(window))
	{
		//process input
		processInput(window);

		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		//set the vao
		glBindVertexArray(quadVAO);
		//draw the quad
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

		//unbind the vao
		glBindVertexArray(0);

		//swap the buffer
		glfwSwapBuffers(window);

		//poll the event
		glfwPollEvents();
	}

	//exit the program 
	glfwTerminate();	

}
