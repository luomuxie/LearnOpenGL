#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class name framebuffers
class framebuffers
{
	//create a func to init the OpenGL
	void initOpenGL();
	//create a window
	GLFWwindow* window;
	//set the window size
	int scale = 2;
	const unsigned int SCR_WIDTH = 800 * scale;
	const unsigned int SCR_HEIGHT = 600 * scale;

	//create a func to init the vertexs
	void initVertexs();
	//create cube vao,vbo
	unsigned int cubeVAO, cubeVBO;
	//create plane vao,vbo
	unsigned int planeVAO, planeVBO;

	//create screen quad VAO and screen quad VBO
	unsigned int quadVAO, quadVBO;

	//create a camera
	Camera camera = Camera(glm::vec3(2.0f, 0.0f, 8.0f));

	//create a func to initFramebuffers
	void initFramebuffers();
	//create framebuffer object
	unsigned int framebuffer;
	//create texture color buffer
	unsigned int textureColorbuffer;
	//create renderbuffer object
	unsigned int rbo;


	//create public func to run
	public:
		void run();
};
