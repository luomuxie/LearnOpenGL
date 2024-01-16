#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
#include <shader_s.h>
//create a class by the name shadow_mapping
class shadow_mapping
{
	//create a func init opengl
	void init_opengl();

	//create a val window's width and height and a sclae factor
	float scale = 3.0f;
	unsigned int SCR_WIDTH = 800 * scale;
	unsigned int SCR_HEIGHT = 600 *scale;

	//create a windown
	GLFWwindow* window;

	//create a func to process input
	void processInput(GLFWwindow* window);

	//create a camera
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	//create a val to store the last frame
	float lastFrame = 0.0f;
	//create a val to store the delta time
	float deltaTime = 0.0f;

	//create a func to init vertex
	void initVertex();

	//create a planeVAO,planeVBO
	unsigned int planeVAO, planeVBO;
	//create a cubeVAO,cubeVBO
	unsigned int cubeVAO, cubeVBO;
	//create a quadVAO,quadVBO
	unsigned int quadVAO, quadVBO;

	//func a func to render scene
	void renderScene(const Shader& shader);

	//create a val to store the depth map size
	const unsigned int SHADOW_WIDTH = 1024*2, SHADOW_HEIGHT = 1024*2;

	//create a val to store the depth map FBO
	unsigned int depthMapFBO;
	//create a val to store the depth map texture
	unsigned int depthMap;
	//create a func to init framebuffer
	void initFramebuffer();
	

	//create a public func to run
	public:
		void run();


};