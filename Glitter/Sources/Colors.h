#pragma once
#include <GLFW/glfw3.h>
//create a class named Colors
class Colors
{
	//create a func to init the openGL
	void initOpenGL();

	//create window
	GLFWwindow* window;

	//create a func to set the vertex data
	void setVertexData();

	//create vao vbo lightvao
	unsigned int VAO, VBO, lightVAO;



	//create a func to init the shader
	void initShader();
	//create the shaderID
	unsigned int shaderID;

	//create a lightshaderID
	unsigned int lightShaderID;



	public:
		void run();
};