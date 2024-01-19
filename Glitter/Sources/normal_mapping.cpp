#include "normal_mapping.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <camera.h>
#include "func.h"
#include "InputUtil.h"

void normal_mapping::init_opengl()
{
	//init glwf
	glfwInit();
	//set opengl version for 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//enable the resize of the window
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(screen_width, screen_height, "LearnOpenGL", nullptr, nullptr);

	//check if the window is created
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	//set the current context
	glfwMakeContextCurrent(window);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		normal_mapping* instance = static_cast<normal_mapping*>(glfwGetWindowUserPointer(window));
		instance->mouse_callback(xpos, ypos);
	});

	//set the callback function for the scroll
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		normal_mapping* instance = static_cast<normal_mapping*>(glfwGetWindowUserPointer(window));
		instance->scroll_callback(xoffset, yoffset);
		});


	//init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
	}

	//set the viewport
	glViewport(0, 0, screen_width, screen_height);

}


void normal_mapping::scroll_callback(double xoffset, double yoffset)
{
	//process the scroll
	camera.ProcessMouseScroll(yoffset);
}


void normal_mapping::mouse_callback( double xpos, double ypos)
{
	InputUtility::mouseCallback(window, xpos, ypos,firstMouse,lastX,lastX,camera);
}

void normal_mapping::run()
{
	init_opengl();
	//main loop 
	while (!glfwWindowShouldClose(window))
	{
		//check if any event is triggered
		glfwPollEvents();

		InputUtility::processInput(window, camera, deltaTime);
		//clear the color buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//swap the back buffer with the front buffer
		glfwSwapBuffers(window);
	}

	//terminte 
	glfwTerminate();
	
}
