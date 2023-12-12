#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class for the geometry_shader_normals
class geometry_shader_normals
{
	//create a func to init the OpenGL
	void initOpenGL();
	//create a window
	GLFWwindow* window;
	//set the window size
	int scale = 3;
	const unsigned int SCR_WIDTH = 800 * scale;
	const unsigned int SCR_HEIGHT = 600 * scale;

	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 12.0f));

	//create a public func to run the geometry_shader_normals
	public:
		void run();
};
