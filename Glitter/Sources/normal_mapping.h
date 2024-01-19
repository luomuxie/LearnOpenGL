#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class by file name
class normal_mapping
{
	//create a func to init the OPengl
	void init_opengl();

	//create a  window
	GLFWwindow  *window;
	//create the window size and the scale
	int scale = 1;
	int screen_width = 640 * scale;
	int screen_height = 480 * scale;	

	//create a camera 
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//create a delta time
	float deltaTime = 0.0f;

	float lastX = 400, lastY = 300;
	bool firstMouse = true;

	//create a func for mouse call back
	void mouse_callback( double xpos, double ypos);


public:
	void run();

	


};
