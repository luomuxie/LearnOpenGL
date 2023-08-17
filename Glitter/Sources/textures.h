#pragma once
//create a class name textures
class textures
{
	//create a func to init the openGL
	void initOpenGL();
	//create a func to set the vertex data
	void setVertexData();
	
	//create window
	GLFWwindow* window;

	//create a VAO, VBO, EBO
	unsigned int VAO, VBO, EBO;

	//create a punblic func to run the program
	public:
		void run();
};
