#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class for anti_aliasing_multisampling
class anti_aliasing_multisampling
{
	//create a func to initOpengl
	void initOpengl();

	//create a window
	GLFWwindow* window;
	//create window width and height and scale val
	int scale = 4;
	int width = 800*scale;
	int height = 600*scale;

	//create a class to init the vertex
	void setVertexData();

	//create a cubevao and cubevbo
	unsigned int cubeVao, cubeVbo;

	// create a camera
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));


	//create a func to run
public :
	void run();
};