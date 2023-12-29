#pragma once
#include <GLFW/glfw3.h>
//create a class for water_ripple_eff
class water_ripple_eff {
	//create a func to initOpengl
	void initOpengl();

	//create a window
	GLFWwindow* window;
	//create window width and height and scale val
	int scale = 4;
	int width = 800 * scale;
	int height = 800 * scale;

	//create a class to init the vertex
	void initVertex();
	//create vao and vbo
	unsigned int vao, vbo;

	//create a func to run
	public:
		void run();

};