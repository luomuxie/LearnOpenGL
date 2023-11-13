#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class for the blending_sorted
class blending_sorted
{
	//create a func to init the OpenGL
	void initOpenGL();
	//create a window
	GLFWwindow* window;
	//set the window size
	int scale = 1;
	const unsigned int SCR_WIDTH = 800 * scale;
	const unsigned int SCR_HEIGHT = 600 * scale;

	//create a func to init the vertexs
	void initVertexs();
	//create cube vao,vbo
	unsigned int cubeVAO, cubeVBO;
	//create plane vao,vbo
	unsigned int planeVAO, planeVBO;

	//create a camera	
	Camera camera = Camera(glm::vec3(2.0f, 0.0f, 8.0f));

	void mouse_callback(double xposIn, double yposIn);
	//create a bool to judge the first mouse
	bool firstMouse = true;
	//create a float to save the last xpos and ypos
	float lastX = 400, lastY = 300;


	void scroll_callback(double xoffset, double yoffset);

	//create a func to process the input
	void processInputs(GLFWwindow* window);

	//create a float to save the deltaTime
	float deltaTime = 0.0f;
	//create a float to save the lastFrame
	float lastFrame = 0.0f;
	
	//create a public func to run the blending_sorted
public:
	void run();

		
};
