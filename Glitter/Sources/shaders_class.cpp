#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "shaders_class.h"
#include <iostream>
#include "func.h"
#include <shader_s.h>


void shaderClass::run()
{
	initOpenGL();
	//init shader use shader_s class
	Shader myshader("..\\Glitter\\Shaders\\shader.vs", "..\\Glitter\\Shaders\\shader.fs");
	myshader.use();
	//set the vertex data
	setVertexData();
	//set the shaderProgram
	//initShaderProgram();
	//set the render loop
	while (!glfwWindowShouldClose(window)) {
		//set the input
		processInput(window);
		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);
		//draw the triangle
		glUseProgram(myshader.ID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	//delete the VAO
	glDeleteVertexArrays(1, &VAO);
	//delete the VBO
	glDeleteBuffers(1, &VBO);	
	//delete the shaderProgram
	glDeleteProgram(myshader.ID);
	//terminate the glfw
	glfwTerminate();

}

void shaderClass::initOpenGL()
{
	//initiate the glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create the window
	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//if the window is null,then print the error
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	//set the current context
	glfwMakeContextCurrent(window);
	//set the callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//initiate the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	//set the viewport
	glViewport(0, 0, 800, 600);
}

void shaderClass::setVertexData()
{
	//create the vertex data and the data of the color
	float vertices[] = {
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};
	
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);	
	//bind the VAO
	glBindVertexArray(VAO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the data of the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	//set the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//enable the position attribute
	glEnableVertexAttribArray(0);
	//set the color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable the color attribute
	glEnableVertexAttribArray(1);

	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the VAO
	glBindVertexArray(0);
}

