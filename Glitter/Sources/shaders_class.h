#pragma once
//create a class name shaderClass
class shaderClass {
	//create a funtion to init OpenGL
	void initOpenGL();
	//create a window
	GLFWwindow* window;

	//create a function to set the vertex data
	void setVertexData();

	// create vao ,vbo,ebo
	unsigned int VAO, VBO;

	//create a public fun to run
	public:
		void run();
};