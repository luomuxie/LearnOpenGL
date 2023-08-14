#include "hellworld.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include "func.h"

//create a window in a func
void hellworld::hellworldOpenGL () {
	// Load GLFW and Create a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	// create mWindow
	GLFWwindow* mWindow = glfwCreateWindow(300, 400, "HelloOpenGL", nullptr, nullptr);		
	// Check for Valid Context
	if (mWindow == nullptr) {
		fprintf(stderr, "Failed to Create OpenGL Context");
		return;
	}
	// Create Context and Load OpenGL Functions
	glfwMakeContextCurrent(mWindow);
	gladLoadGL();
	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
	//call back
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	// Rendering Loop
	while (glfwWindowShouldClose(mWindow) == false) {
		processInput(mWindow);
		// Background Fill bule Color

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Flip Buffers and Draw
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}   
	glfwTerminate();
	return;
}
