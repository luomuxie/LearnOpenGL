#include "model_loading.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "func.h"

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
	//set the callback function for the resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
