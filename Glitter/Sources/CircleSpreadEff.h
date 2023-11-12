#pragma once
#include <GLFW/glfw3.h>
//create a class name CircleSpreadEff
class CircleSpreadEff
{
	//create a func to init the openGL
	void initOpenGL();
	//create a window and the window size
	GLFWwindow* window;
	const unsigned int SCR_WIDTH = 800*4;
	const unsigned int SCR_HEIGHT = 600*4;
	//create a func to init the vertex
	void initVertex();
	//create vao and vbo
	unsigned int VAO, VBO;


	//create a public func to run the program
	public:
		void run();

};
