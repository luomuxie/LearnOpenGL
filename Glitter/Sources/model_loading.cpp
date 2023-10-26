#include "model_loading.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "func.h"
#include <shader_s.h>
#include <model.h>
#include <glm/gtc/type_ptr.hpp>


void ModelLoading::initOpenGL()
{
	//init the OpenGL
	glfwInit();
	//set the version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the OpenGL to use the core-profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//enble the resize
	glfwWindowHint(GLFW_RESIZABLE, false);

	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Model Loading", NULL, NULL);

	//judge if the window is created
	if (window == NULL)
	{
		//print the error
		std::cout << "Failed to create GLFW window" << std::endl;
		//end the program
		glfwTerminate();
		return;
	}

	 //set the window to the current context
	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, this);
	//set the callback function for the resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		ModelLoading* instance = static_cast<ModelLoading*>(glfwGetWindowUserPointer(window));
		instance->mouse_callback(xpos, ypos);
		});

	//glfwSetScrollCallback(window, scroll_callback);
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		ModelLoading* instance = static_cast<ModelLoading*>(glfwGetWindowUserPointer(window));
		instance->scroll_callback(xoffset, yoffset);
		});

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	
	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//print the error
		std::cout << "Failed to initialize GLAD" << std::endl;
		//end the program
		return;
	}
	//set the viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}


void ModelLoading::processInput(GLFWwindow* window)
{
	//if the user press the esc
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//close the window
		glfwSetWindowShouldClose(window, true);
	}
	//if the user press the W
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//move the camera forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	//if the user press the S
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//move the camera backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	//if the user press the A
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//move the camera left
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	//if the user press the D
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//move the camera right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}


void ModelLoading::mouse_callback( double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);	
}

void ModelLoading::scroll_callback(double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void ModelLoading::run()
{
	//init the OpenGL
	initOpenGL();
	//stbi_set_flip_vertically_on_load(false);
	//init the shader	
	Shader ourShader("..\\Glitter\\Shaders\\model_loading.vs", "..\\Glitter\\Shaders\\model_loading.fs");
	//load the model	
	Model ourModel("..\\Glitter\\Resources\\Objects\\nanosuit\\nanosuit.obj");
	

	//set the render loop
	while (!glfwWindowShouldClose(window))
	{
		//set the time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//process the input
		processInput(window);
		//print the camera position

		//set the color of the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set the shader
		ourShader.use();

		//set the view matrix
		glm::mat4 view = camera.GetViewMatrix();
		//set the view matrix use glm
		glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

		//set the projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
			0.1f, 100.0f);
		//set the projection matrix use glm
		glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		//set the model matrix
		glm::mat4 model = glm::mat4(1.0f);
		//set the model matrix use glm
		glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		

		//draw the model
		ourModel.Draw(ourShader);

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}

	//end the program
	glfwTerminate();
	return;

}



