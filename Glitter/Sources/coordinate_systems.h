#pragma once
//create a class named coordinate_systems
class coordinate_systems
{
	//create a func to init the openGL
	void initOpenGL();

	//create window
	GLFWwindow* window;

	//create a func to set the vertex data
	void setVertexData();

	//create vao vbo ebo texture
	unsigned int VAO, VBO, EBO, texture;

	//create a func to init the shader
	void initShader();
	//create the shaderID
	unsigned int shaderID;

	//create a func to load the texture
	void loadTexture();

	//create a public func to run the program
	public:
		void run();
};

