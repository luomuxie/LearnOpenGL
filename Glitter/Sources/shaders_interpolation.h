#pragma once
class shaders_interpolation
{
	//create a function to initOpenGL
	void initOpenGL();
	//create a window
	GLFWwindow* window;

	//create a function to set the vertex data
	void setVertexData();

	//create a function to init the shaderProgram
	void initShaderProgram();

	public:
		void run();

	//create the VAO,VBO,EBO
	unsigned int VAO, VBO, EBO;
	//create the shaderProgram
	unsigned int shaderProgram;

};

