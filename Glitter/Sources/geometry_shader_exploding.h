#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class for geometry_shader_exploding
class geometry_shader_exploding
{

	//create a func to init the opengl
	void init_opengl();
	//create a window
	GLFWwindow* window;
	//create the window width and height
	//create a scale for the window
	float scale = 4.0f;
	int WIDTH = 800*scale;
	int HEIGHT = 600*scale;

	//create a func to init the vertex
	//void init_vertex();

	////create the cube vao and vbo
	//unsigned int cubeVAO, cubeVBO;
	////create the skybox vao and vbo
	//unsigned int skyboxVAO, skyboxVBO;

	//create a camera
	Camera camera = Camera(glm::vec3(0.0f, -3.0f, -12.0f));

	////create a public func to run
	//	//create mouse callback
	//void mouse_callback(double xposIn, double yposIn);
	////create first mouse
	//bool firstMouse = true;
	////create lastX, lastY
	//float lastX = 400.0f;
	//float lastY = 300.0f;

	////create scroll callback 
	//void scroll_callback(double xoffset, double yoffset);
	////create deltaTime, lastFrame
	//float deltaTime = 0.0f;
	//float lastFrame = 0.0f;
	//void processInputs(GLFWwindow* window);

	////create a func to load the texture
	//unsigned int loadTextures(char const* path);

	//create a public func to run
	public:
		void run();


};
