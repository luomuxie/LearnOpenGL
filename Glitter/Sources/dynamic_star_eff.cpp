#include "dynamic_star_eff.h"
#include <iostream>
#include <glad/glad.h>
#include <shader_s.h>
#include "Constants.h"

void dynamic_star_eff::init_opengl()
{
	//init the glfw
	glfwInit();

	//set the version of opengl	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the opengl profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window can resizeable
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);


	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "dynamic_star_eff", NULL, NULL);
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
	//set the viewport
	glViewport(0, 0, WIDTH, HEIGHT);
}

void dynamic_star_eff::init_vertex()
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

void dynamic_star_eff::run()
{
	//init the opengl
	init_opengl();
	//init the vertex
	init_vertex();

	//set the shader
	Shader shader((SHADER_PATH + "dynamic_star_eff.vs").c_str(), (SHADER_PATH + "dynamic_star_eff.fs").c_str());

	//set the loop
	while (!glfwWindowShouldClose(window))
	{

		//set the color of the screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set the shader
		shader.use();

		//create a vec2 to store the resolution
		glm::vec2 resolution;
		resolution.x = WIDTH;
		resolution.y = HEIGHT;

		shader.setVec2("iResolution", resolution);
		//set the shader Attrubute
		shader.setFloat("iTime", glfwGetTime());

		//bind the vao
		glBindVertexArray(VAO);
		//draw the plane
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
