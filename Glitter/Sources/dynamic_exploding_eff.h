#pragma once
#include <GLFW/glfw3.h>
#include "camera.h"
//create a class for dynamic_exploding_eff
class dynamic_exploding_eff
{
	//create a func to initOpengl
	void initOpengl();

	//create a window
	GLFWwindow* window;
	//create window width and height and scale val
	int scale = 4;
	int width = 800*scale;
	int height = 600*scale;

	//create a camera
	Camera camera = Camera(glm::vec3(0.0f, -3.0f, -12.0f));

	//create a func to run
public:
	void run();

};