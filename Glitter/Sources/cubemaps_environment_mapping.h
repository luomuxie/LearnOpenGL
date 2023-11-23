#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class for cubemaps_enviroment_mapping
class cubemaps_environment_mapping
{

	//create a func to init the opengl
	void init_opengl();
	//create a window
	GLFWwindow* window;
	//create the window width and height
	//create a scale for the window
	float scale = 1.0f;
	int WIDTH = 800*scale;
	int HEIGHT = 600*scale;

	//create a func to init the vertex
	void init_vertex();

	//create the cube vao and vbo
	unsigned int cubeVAO, cubeVBO;
	//create the skybox vao and vbo
	unsigned int skyboxVAO, skyboxVBO;

	//create a camera
	Camera camera = Camera(glm::vec3(2.0f, 0.0f, 8.0f));

	//create a public func to run
		//create mouse callback
	void mouse_callback(double xposIn, double yposIn);
	//create first mouse
	bool firstMouse = true;
	//create lastX, lastY
	float lastX = 400.0f;
	float lastY = 300.0f;

	//create scroll callback 
	void scroll_callback(double xoffset, double yoffset);
	//create deltaTime, lastFrame
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	void processInputs(GLFWwindow* window);

public:
	void run();




};


