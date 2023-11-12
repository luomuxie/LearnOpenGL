#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class for the daynamic spread eff
class DynamicSpreadEffect
{
	//create a func to initOpenGL
	void initOpenGL();
	//create a window and the window size
	GLFWwindow* window;
	int scale = 1;
	const unsigned int SCR_WIDTH = 800 * scale;
	const unsigned int SCR_HEIGHT = 600 * scale;

	//create a func to init vertices
	void initVertices();
	//create a vao and vbo
	unsigned int VAO, VBO;

	//create a func to init shader
	//void initShader();


	public:
		void run();
};
