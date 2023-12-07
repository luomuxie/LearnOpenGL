#include "geometry_shader_houses.h"
#include <iostream>
#include <glad/glad.h>
#include "func.h"
#include <shader_s.h>
#include "Constants.h"

void geometry_shader_houses::initOpenGL()
{
	//initglwf
	glfwInit();
	//set the version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the opengl profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window can resizeable
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//create a window 
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "geometry_shader_houses", NULL, NULL);

	//judge if the window create successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	//set the window to the main thread
	glfwMakeContextCurrent(window);

	//init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
	}

	//set the view size
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	
	
}

void geometry_shader_houses::setVertexData()
{
	//create a plane vertices with four
	float vertices[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
		-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // 左下
	};

	//set the vao and vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind the vao and vbo
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//set the data of vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//set the attribute of vbo
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//set the attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//unbind the vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void geometry_shader_houses::run()
{
	//init the opengl
	initOpenGL();
	//init the vertex
	setVertexData();

	//init shader
	Shader shader((SHADER_PATH + "geometry_shader_houses.vs").c_str(), (SHADER_PATH + "geometry_shader_houses.fs").c_str(), (SHADER_PATH + "geometry_shader_houses.gs").c_str());

	//main loop 
	while (!glfwWindowShouldClose(window))
	{
		//set the input
		processInput(window);

		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//set the shader
		shader.use();
				
		//bind the vao
		glBindVertexArray(VAO);
		//draw the triangle
		glDrawArrays(GL_POINTS, 0, 4);
		//unbind the vao
		glBindVertexArray(0);

		//swap the buffer
		glfwSwapBuffers(window);
		//set the event
		glfwPollEvents();
	}

}
