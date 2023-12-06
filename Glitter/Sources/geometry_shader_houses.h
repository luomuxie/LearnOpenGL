#pragma once
#include <GLFW/glfw3.h>
//create a class name geometry_shader_houses
class geometry_shader_houses
{
	//create a func to init the openGL
	void initOpenGL();
	//create a func to set the vertex data
	void setVertexData();

	//create a func to load the texture
	//void loadTexture();

	//create window
	GLFWwindow* window;
	//window's with and height
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	//create a VAO, VBO
	unsigned int VAO, VBO;

	
	//create a punblic func to run the program
	public:
		void run();
};