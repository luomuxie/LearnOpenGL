#pragma once
#include <GLFW/glfw3.h>
//create a class name camera
class hello_camera
{
	//create a func to init the openGL
	void initOpenGL();
	//create a func to set the vertex data
	void setVertexData();
	//create a func to set the texture data
	void setTextureData();
	//create a func to set the shader data
	void setShaderData();

	//create window
	GLFWwindow* window;

	//create a VAO, VBO,Texture
	unsigned int VAO, VBO, texture;
	
	//create a shaderID
	unsigned int shaderID;
	
	//create a public func to run the program
	public:
		void run();

};
