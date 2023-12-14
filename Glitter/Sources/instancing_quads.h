#pragma once
#include <GLFW/glfw3.h>
//create a class for instancing_quads
class instancing_quads
{
	//create a func to initOpenGL
	void initOpenGL();

	//create val window's width and height

	float scale = 1.0f;
	int SCR_WIDTH = 800 * scale;
	int SCR_HEIGHT = 600 * scale;

	//create a window
	GLFWwindow* window;

	//create a func to initVertex
	void initVertex();

	//create quadVAO,quadVBO
	unsigned int quadVAO, quadVBO;

	//create instanceVBO
	unsigned int instanceVBO;
	

	//create a public func to run
public:
	void run();


};