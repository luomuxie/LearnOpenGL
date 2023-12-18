#include "dynamic_exploding_eff.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <shader_s.h>
#include <model.h>
#include "func.h"
#include "Constants.h"

void dynamic_exploding_eff::initOpengl()
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
	window = glfwCreateWindow(width, height, "dynamic_exploding_eff", nullptr, nullptr);

	//if the window is not created, print error msg
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	//set the window to the current context
	glfwMakeContextCurrent(window);

	//init glad;
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
	}

	//set the size of the viewport
	glViewport(0, 0, width, height);
	
}

void dynamic_exploding_eff::run()
{
	//init opengl 
	initOpengl();

	//load the shader
	Shader shader((SHADER_PATH + "dynamic_exploding_eff.vs").c_str(), (SHADER_PATH+ "dynamic_exploding_eff.fs").c_str(),(SHADER_PATH + "dynamic_exploding_eff.gs").c_str());

	//load the model
	Model ourModel((MODEL_PATH + "nanosuit\\nanosuit.obj").c_str());

	//open depth test;
	glEnable(GL_DEPTH_TEST);
	
	//create main loop
	while (!glfwWindowShouldClose(window))
	{
		//process input
		processInput(window);

		//set the color of the screen
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		//clear the color buffer and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use the shader
		shader.use();

		//create a model matrix
		glm::mat4 model = glm::mat4(0.05f);

		model = glm::translate(model, glm::vec3(0.0f, -12.0f, -29.0f));

		//rotate the model with a speed
		model = glm::rotate(model, (float)glfwGetTime() * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));

		//create a view matrix
		glm::mat4 view = camera.GetViewMatrix();
		//create projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);

		//set the value of the uniform
		shader.setMat4(shader.MODEL, model);
		shader.setMat4(shader.VIEW, view);
		shader.setMat4(shader.PROJECTION, projection);

		//set the time
		shader.setFloat("time", glfwGetTime());

		ourModel.Draw(shader);
		//swap the buffer
		glfwSwapBuffers(window);

		//poll the event
		glfwPollEvents();
	}
	//end the program
	glfwTerminate();
}
