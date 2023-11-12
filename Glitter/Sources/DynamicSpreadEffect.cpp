#include "DynamicSpreadEffect.h"
#include <iostream>
#include "shader_s.h"
#include "func.h"

void DynamicSpreadEffect::initOpenGL()
{
	//init glfw
	glfwInit();
	//set the version of glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the profile of glfw
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dynamic Spread Effect", NULL, NULL);
	//check if the window is created
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}
	//set the window to the current context
	glfwMakeContextCurrent(window);
	
	//set the callback for framebuffer size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//set the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

		//return -1;
	}
	//set the viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void DynamicSpreadEffect::initVertices()
{
	//create a plane vertices with four
	float vertices[] = {
	-1.0f, -1.0f,  // ×óÏÂ½Ç
	 1.0f, -1.0f,  // ÓÒÏÂ½Ç
	-1.0f,  1.0f,  // ×óÉÏ½Ç
	 1.0f,  1.0f   // ÓÒÉÏ½Ç
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//unbind the vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}




void DynamicSpreadEffect::run()
{
	//init the opengl
	initOpenGL();
	//init the vertices
	initVertices();
	//init the shader by shader class
	Shader shader("..\\Glitter\\Shaders\\dynamic_spread_effect.vs", "..\\Glitter\\Shaders\\dynamic_spread_effect.fs");
	
			
	//main render
	while (!glfwWindowShouldClose(window))
	{
		//process the input
		processInput(window);
		//get the delta time

		//clear the color buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//set the shader
		shader.use();
		//set the iResolution
		//create a vec2 to store the resolution
		glm::vec2 resolution;
		resolution.x = SCR_WIDTH;
		resolution.y = SCR_HEIGHT;
		shader.setVec2("iResolution", resolution);
		//set the shader Attrubute
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

	//clear the glfw
	glfwTerminate();

	
}

