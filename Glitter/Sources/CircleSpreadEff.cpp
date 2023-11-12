#include "CircleSpreadEff.h"
#include <iostream>
#include <glad/glad.h>
#include "func.h"
#include <shader_s.h>

void CircleSpreadEff::initOpenGL()
{
	//initOpenGL
	glfwInit();
	//set the version of openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL to use the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CircleSpreadEff", NULL, NULL);
	//if the window is not created, then print the error
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}
	//set the window to the main context
	glfwMakeContextCurrent(window);
	//set the frame buffer size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		//return -1;
	}
	//set the view port
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

}

void CircleSpreadEff::initVertex()
{
	//create a plane vertex with four pos
	float vertices[] = {
		-1.0f , -1.0f,
		1.0f , -1.0f,
		-1.0f , 1.0f,
		1.0f , 1.0f
	};

	//set the vao and vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind the vao and vbo
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//set the data fo vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//set the vertex attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind the vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void CircleSpreadEff::run()
{
	//init the openGL
	initOpenGL();
	//init the vertex
	initVertex();

	//init the shader by the shader class
	Shader shader("..\\Glitter\\Shaders\\CircleSpreadEff.vs", "..\\Glitter\\Shaders\\CircleSpreadEff.fs");

	
	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//process the input
		processInput(window);
		//set the color of the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//clear the color buffer and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//use the shader
		shader.use();
		//set the iResolution
		//create a vec2 to store the resolution
		glm::vec2 resolution;
		resolution.x = SCR_WIDTH;
		resolution.y = SCR_HEIGHT;
		//set the iResolution
		shader.setVec2("iResolution", resolution);
		//set the iTime
		shader.setFloat("iTime", glfwGetTime());

		//bind the vao
		glBindVertexArray(VAO);
		//draw the rectangle
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//unbind the vao
		glBindVertexArray(0);


		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}

}
