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

	//create vao vbo lightvao
	unsigned int VAO, VBO, lightVAO;
	
	//create the shaderID
	unsigned int shaderID;

	//create a lightshaderID
	unsigned int lightShaderID;

	const unsigned int SCR_WIDTH = 1024;
	const unsigned int SCR_HEIGHT = 720;
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	

	public:
		void run();
};