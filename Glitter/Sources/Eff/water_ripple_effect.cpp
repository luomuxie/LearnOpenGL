#include "water_ripple_effect.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <shader_s.h>
#include "Constants.h"

void WaterRippleEffect::initOpenGL()
{
	//init glfw
	glfwInit();

	//set opengl version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//set opengl profile to core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window to be resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create a window
	window = glfwCreateWindow(width, height, "Water Ripple Effect", nullptr, nullptr);

	//check if the window is created
	if (window == nullptr)
	{
		//if the window is not created then terminate the program
		glfwTerminate();
	}

	//set the window to be the current context
	glfwMakeContextCurrent(window);

	//init glad to load the opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//if glad fails to load then terminate the program
		glfwTerminate();
	}

	//set the viewport
	glViewport(0, 0, width, height);
}

void WaterRippleEffect::initVertex()
{
	//create a plane vertex with 4 vertices
	float plane[] = {
		// positions
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f
	};

	//set the vao and vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind the vao and vbo 
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//set the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);

	//set the vertex attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind the vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void WaterRippleEffect::run()
{
	//init opengl
	initOpenGL();

	//init the vertex
	initVertex();
	//add shader for the plane
	Shader planeShader((SHADER_Eff_PATH + "water_ripple_effect.vs").c_str(), (SHADER_Eff_PATH + "water_ripple_effect.fs").c_str());

	//create a loop to run the program
	while (!glfwWindowShouldClose(window))
	{
		//set the background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//use the shader
		planeShader.use();		
		
		//draw the plane
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		//swap the buffer
		glfwSwapBuffers(window);

		//poll the event
		glfwPollEvents();
	}
	//end the program
	glfwTerminate();
	
}
