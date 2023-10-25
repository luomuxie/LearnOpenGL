#pragma once
//create a class for the model loading
#include <GLFW/glfw3.h>
#include <camera.h>
class ModelLoading
{
	//create a func to initOpenGL
	void initOpenGL();
	//create a window and the window size
	GLFWwindow* window;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	//create a func to process the input
	void processInput(GLFWwindow* window);
	//create a camera
	Camera camera = Camera(glm::vec3(0.0f, 3.0f, 30.0f));
	//create delta time
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//creat a func to process the mouse
	void mouse_callback( double xposIn, double yposIn);
	//create a bool to check the first mouse
	bool firstMouse = true;
	//create a float to check the last x and y
	float lastX = 400, lastY = 300;
	
	//create a func to process the scroll
	void scroll_callback( double xoffset, double yoffset);




public:
//create a func to run the model loading
	void run();

	
};