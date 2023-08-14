#pragma once
#include <GLFW/glfw3.h>
class hello_rect
{
	public:
		void hello_rectOpenGL();
	void initOpenGL();

	void setVertexData();

	void initShader();

	//create private variables
	GLFWwindow* window;
	unsigned int shaderProgram;
	unsigned int VBO, VAO;
};

