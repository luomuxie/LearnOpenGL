#pragma once
#include <GLFW/glfw3.h>
//create a class for the star effect
class StarEff
{
	//init OpenGL
	void initOpenGL();

	//create a window
	GLFWwindow* window;
	
	//create the window width and height
	//create a scale for the window
	
	float scale = 3.0f;
	int width = 800*scale;
	int height = 600* scale;

	//init Vertex
	void initVertex();

	//create vao vbo
	unsigned int vao, vbo;

	//create a public function for the star effect
	public:
		void run();


};