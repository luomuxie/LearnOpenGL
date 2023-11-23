#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class name cubemaps_skybox
class cubemaps_skybox
{
	//create a func to init the OpenGL
	void initOpenGL();

	GLFWwindow* window;
	//set the window size
	int scale = 1;
	const unsigned int SCR_WIDTH = 800 * scale;
	const unsigned int SCR_HEIGHT = 600 * scale;

	//create a func to init the vertex
	void initVertex();
	//create cubeVAO, cubeVBO
	unsigned int cubeVAO, cubeVBO;
	//create a camera
	Camera camera = Camera(glm::vec3(2.0f, 0.0f, 8.0f));
	
	//create skyboxVAO, skyboxVBO
	unsigned int skyboxVAO, skyboxVBO;

	//create a func to inputprocess
	void processInputs(GLFWwindow* window);
	//create deltaTime, lastFrame
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//create mouse callback
	void mouse_callback(double xposIn, double yposIn);
	//create first mouse
	bool firstMouse = true;
	//create lastX, lastY
	float lastX = 400.0f;
	float lastY = 300.0f;

	//create scroll callback 
	void scroll_callback(double xoffset, double yoffset);

	//create a public func to run
public:
	void run();

};


