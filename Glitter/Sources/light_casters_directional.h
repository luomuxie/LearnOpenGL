#pragma once
#include <GLFW/glfw3.h>
//create a class for the directional light
class light_casters_directional
{
	//create a func to init the OpenGL
	void initOpenGL();
	//create a window and the window size
	GLFWwindow* window;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	//create a func to access the input
	void processInputColor(GLFWwindow* window);
	//create a func to set the vertex data
	void setVertexData();
	//create lightVAO,cubeVAO,VBO
	unsigned int lightVAO, cubeVAO, VBO;

	//create a public func to run
	public:
		void run();

};