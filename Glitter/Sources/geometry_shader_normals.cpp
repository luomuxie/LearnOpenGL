#include "geometry_shader_normals.h"
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <model.h>
#include "Constants.h"



void geometry_shader_normals::initOpenGL()
{
	//glfw
	glfwInit();
	//set the version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the opengl profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//set the window can resizeable
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//init the window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "geometry_shader_normals", NULL, NULL);
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
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

}

void geometry_shader_normals::run()
{
	initOpenGL();
	//initvertexs();
	//init the shader
	Shader normalShader((SHADER_PATH + "geometry_shader_normals.vs").c_str(), (SHADER_PATH + "geometry_shader_normals.fs").c_str(), (SHADER_PATH + "geometry_shader_normals.gs").c_str());
	Shader shader((SHADER_PATH + "model_loading.vs").c_str(), (SHADER_PATH + "model_loading.fs").c_str());

	//load the model
	Model ourModel((MODEL_PATH + "nanosuit\\nanosuit.obj").c_str());


	//open the depth test
	glEnable(GL_DEPTH_TEST);
	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//process the input
		processInput(window);
		//set the color of the screen
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw the triangle
		shader.use();
		//create a model matrix
		glm::mat4 model = glm::mat4(1.0f);

		//move the model to far
		model = glm::translate(model, glm::vec3(0.0f, -12.0f, 0.0f));

		//create a view matrix
		glm::mat4 view = camera.GetViewMatrix();
		//create a projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		//set the uniform
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		//draw the model
		ourModel.Draw(shader);

		normalShader.use();
		normalShader.setMat4(shader.MODEL, model);
		normalShader.setMat4(shader.VIEW, view);
		normalShader.setMat4(shader.PROJECTION, projection);
		//draw the model
		ourModel.Draw(normalShader);

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}

	//exit the program
	glfwTerminate();
}