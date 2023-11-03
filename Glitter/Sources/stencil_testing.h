#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class for the stencil testing
class stencil_testing
{
	//create a func to initOpenGL
	void initOpenGL();
	//create a window and the window size
	GLFWwindow* window; 
	int scale = 2;
	const unsigned int SCR_WIDTH = 800*scale;
	const unsigned int SCR_HEIGHT = 600*scale;

	//create a func to callback for mouse
	void mouse_callback(double xposIn, double yposIn);
	//create a bool to check the first mouse
	bool firstMouse = true;
	//create a float to check the last x and y
	float lastX = 400, lastY = 300;

	//create a func to callback for scroll
	void scroll_callback(double xoffset, double yoffset);
	//create a camera
	Camera camera = Camera(glm::vec3(2.0f, 0.0f, 8.0f));

	//create a func to process the input
	void processInput(GLFWwindow* window);
	//create delta time
	float deltaTime = 0.0f;

	//create a func to init vertices
	void initVertices();
	//create cube VAO and cube VBO
	unsigned int cubeVAO, cubeVBO;
	//create plane VAO and plane VBO
	unsigned int planeVAO, planeVBO;
	
	//create a float
	float lastFrame = 0;

public:
	void run();
	
};



