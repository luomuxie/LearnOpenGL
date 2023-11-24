#pragma once
#include <GLFW/glfw3.h>
//create a class for dynamic_star_eff
class dynamic_star_eff
{
	//create a func to init the opengl
	void init_opengl();
	//create a window
	GLFWwindow* window;
	//create the window width and height
	//create a scale for the window
	float scale = 1.0f;
	int WIDTH = 800 * scale;
	int HEIGHT = 600 * scale;

	//create a func to init the vertex
	void init_vertex();

	//create the vao and vbo
	unsigned int VAO, VBO;

//create a public func to run
public:
	void run();
};