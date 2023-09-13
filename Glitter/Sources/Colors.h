#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class named Colors
class Colors
{
	//create a func to init the openGL
	void initOpenGL();

	//create window
	GLFWwindow* window;

	//create a func to set the vertex data
	void setVertexData();

	//create a func to init the shader
	void initShader();

	void processInputColor(GLFWwindow* window);
	//create vao vbo lightvao
	unsigned int VAO, VBO, lightVAO;
	
	//create the shaderID
	unsigned int shaderID;

	//create a lightshaderID
	unsigned int lightShaderID;


	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	Camera camera = Camera(
		glm::vec3(3.7342, 2.0652f, -1.6181f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		144.3973f,
		-26.8f
		);
	glm::vec3 lightPos = glm::vec3(0.8f, 0.5f, 2.0f);
	

	public:
		void run();
		
};