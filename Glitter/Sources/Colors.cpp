#include <glad/glad.h>
#include "Colors.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "func.h"
#include <shader_s.h>


void Colors::initOpenGL()
{
	//init the glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL to use the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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
	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}	
}

void Colors::setVertexData()
{
	//create a cube vertex data array 
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f,  0.5f, -0.5f,  
		 0.5f,  0.5f, -0.5f,  
		-0.5f,  0.5f, -0.5f,  
		-0.5f, -0.5f, -0.5f,  

		-0.5f, -0.5f,  0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  
		-0.5f, -0.5f,  0.5f,  

		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f,  
		-0.5f, -0.5f, -0.5f,  
		-0.5f, -0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  

		 0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  

		-0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f, -0.5f,  0.5f,  
		-0.5f, -0.5f,  0.5f,  
		-0.5f, -0.5f, -0.5f,  

		-0.5f,  0.5f, -0.5f,  
		 0.5f,  0.5f, -0.5f,  
		 0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f, -0.5f,  
	};

	//create a VAO
	glGenVertexArrays(1, &VAO);
	//create a VBO
	glGenBuffers(1, &VBO);
	//bind the VAO
	glBindVertexArray(VAO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the VBO data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	
	//set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//create light VAO
	glGenVertexArrays(1, &lightVAO);
	//bind the light VAO
	glBindVertexArray(lightVAO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	

	//enable the vertex attribute
	glEnableVertexAttribArray(0);
	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the VAO
	glBindVertexArray(0);	
}


void Colors::initShader()
{
	//create shader frome shader class
	Shader ourShader("shader.vs", "shader.fs");
	//use the shader
	ourShader.use();
	//set shaderID
	shaderID = ourShader.ID;
}

void Colors::run()
{
	//init the openGL
	initOpenGL();
	//set the vertex data
	setVertexData();
	//init the shader
	initShader();
	//render loop
	while (!glfwWindowShouldClose(window)) {
		//process the input
		processInput(window);
		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);


		//draw the cube
		glUseProgram(shaderID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//draw the light
		glUseProgram(shaderID);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	//delete the VAO
	glDeleteVertexArrays(1, &VAO);
	//delete the VBO
	glDeleteBuffers(1, &VBO);
	//delete the shader program
	glDeleteProgram(shaderID);
	//delete the window
	glfwTerminate();
}
