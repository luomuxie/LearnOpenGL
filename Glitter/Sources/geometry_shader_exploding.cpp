#include "geometry_shader_exploding.h"
#include <iostream>
#include <glad/glad.h>
#include "func.h"
#include <shader_s.h>
#include <model.h>
#include "Constants.h"


void geometry_shader_exploding::init_opengl()
{
	//init glfw
	glfwInit();
	//set the version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the opengl profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//set the window can resizeable
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "geometry_shader_exploding", NULL, NULL);
	//if the window create failed
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
	glViewport(0, 0, WIDTH, HEIGHT);		
}

void geometry_shader_exploding::run()
{
	//init the opengl
	init_opengl();
	
	//load the shader 
	Shader shader((SHADER_PATH+"geometry_shader_exploding.vs").c_str(), (SHADER_PATH + "model_loading.fs").c_str(), (SHADER_PATH + "geometry_shader_exploding.gs").c_str());
	
	//use the model to load the model
	Model ourModel((MODEL_PATH + "nanosuit\\nanosuit.obj").c_str());

	//open the depth test
	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window))
	{
		//process the input
		processInput(window);

		//set the background color
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set the shader
		shader.use();

		//create a model matrix
		glm::mat4 model = glm::mat4(0.05f);

		//move the model to far
		model = glm::translate(model, glm::vec3(0.0f, -12.0f, -24.0f));
		//rotate the model by loop with a speed
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		

		//create a view matrix
		glm::mat4 view = camera.GetViewMatrix();
		//create a projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		//set the uniform
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		//set the time
		float time = glfwGetTime();
		shader.setFloat("time", time);

		ourModel.Draw(shader);

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}

	//end the program
	glfwTerminate();
	
}
