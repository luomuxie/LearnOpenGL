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
	int scale = 1;
	int SCR_WIDTH = 800;
	int SCR_HEIGHT = 600;

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

	
	//create a public func to run
public:
	
	void run();
};


