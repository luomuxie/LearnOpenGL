#pragma once
#include <GLFW/glfw3.h>
//create a class for shadow_mapping_depth
class shadow_mapping_depth
{
	//create a func to initOpenGL
	void initOpenGL();

	//create val window's width and height

	float scale = 1.0f;
	unsigned int SCR_WIDTH = 800 * scale;
	unsigned int SCR_HEIGHT = 600 * scale;

	//create a window
	GLFWwindow* window;

	//create a func to initVertex
	void initVertex();

	//create planeVAO,planeVBO
	unsigned int planeVAO, planeVBO;
	//create cubeVAO,cubeVBO
	unsigned int cubeVAO, cubeVBO;

	//create depth map size
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	//create depth map FBO
	unsigned int depthMapFBO;

	//create a func to init framebuffer
	void initFramebuffer();


	//create a func to run 
public:
	void run();

};