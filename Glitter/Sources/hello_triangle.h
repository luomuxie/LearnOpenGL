#pragma once
#include <GLFW/glfw3.h>
class hello_triangle
{
	
	void initShader();
	void setVertexData();
	void initOpenGL();

	GLFWwindow* window;
	unsigned int shaderProgram;
	unsigned int VBO, VAO;

public:
	void hello_triangleOpenGL();
};

