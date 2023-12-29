#pragma once
#include <GLFW/glfw3.h>
//create a class for the water ripple effect
class WaterRippleEffect
{
	//create a func to initopenGl
	void initOpenGL();

	//creaet a  window
	GLFWwindow* window;
	//create the size of the window
	//create a int val to scale the window
	int scale = 1;

	int width = 800*scale;
	int height = 800 *scale;

	//create a func to init the vertex
	void initVertex();
	//create vao and vbo
	unsigned int VAO, VBO;

	//create a func to run the program
public :
	void run();


};
