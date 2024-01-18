#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
#include <shader_s.h>
//create a class name point_shadows
class point_shadows
{
	//create a func to init the OpenGL
	void init_opengl();

	//create a window size and a scale val
	int scale = 3;
	int SCR_WIDTH = 800*scale;
	int SCR_HEIGHT = 600*scale;

	//create a window 
	GLFWwindow *window;

	//create a camera
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//create a func to aceess the input
	void processInput(GLFWwindow *window);

	//create a delta time
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//create a func to init the vertex data
	void init_vertex_data();

	//create plane VAO, VBO
	unsigned int planeVAO, planeVBO;
	//create cube VAO, VBO
	unsigned int cubeVAO, cubeVBO;
	//create quad VAO, VBO
	unsigned int quadVAO, quadVBO;

	//create a func to init the frame buffer
	void init_frame_buffer();

	//create depth map FBO and texture
	unsigned int depthMapFBO;
	unsigned int depthCubemap;

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;


	void renderScene(const Shader& shader);

	//create a func to mouse callback
	void mouse_callback( double xpos, double ypos);
	//create float to store the last x and y pos and first mouse
	float lastX = 400, lastY = 300;
	bool firstMouse = true;

	//create a func to scroll callback
	void scroll_callback(double xoffset, double yoffset);

	//create a bool  for the shadows
	bool shadows = true;	
	
	//create a public func to run
public:
	
	void run();
};


