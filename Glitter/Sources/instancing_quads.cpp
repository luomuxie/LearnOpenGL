
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

	
	
	//create translations array
	glm::vec2 translations[100];
	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}


	//store the instance data in an array buffer
	glGenBuffers(1, &instanceVBO);
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
	
	//--------------------------------------------------------------------------------------

	//glGenVertexArrays(1, &quadVAO);
	//glGenBuffers(1, &quadVBO);

	//glBindVertexArray(quadVAO);
	//glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	////also set instance data
	//glEnableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.



	//unbind the vao and vbo
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//
	//glm::vec2 translations[100];
	//int index = 0;
	//float offset = 0.1f;
	//for (int y = -10; y < 10; y += 2)
	//{
	//	for (int x = -10; x < 10; x += 2)
	//	{
	//		glm::vec2 translation;
	//		translation.x = (float)x / 10.0f + offset;
	//		translation.y = (float)y / 10.0f + offset;
	//		translations[index++] = translation;
	//	}
	//}

	////// store instance data in an array buffer
	////// --------------------------------------
	////
	//glGenBuffers(1, &instanceVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	////// set up vertex data (and buffer(s)) and configure vertex attributes
	////// ------------------------------------------------------------------
	//float quadVertices[] = {
	//	// positions     // colors
	//	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
	//	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
	//	-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

	//	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
	//	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
	//	 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
	//};	 
	//glGenVertexArrays(1, &quadVAO);
	//glGenBuffers(1, &quadVBO);

	//glBindVertexArray(quadVAO);
	//glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	//// also set instance data
	//glEnableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.
	
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
