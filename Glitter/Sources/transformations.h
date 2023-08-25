#pragma once
//create a class name transformations
class transformations
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

	//create a VAO, VBO, EBO
	unsigned int VAO, VBO, EBO;
	//create a texture
	unsigned int texture1;

	//create a shaderID
	unsigned int shaderID;

public:
	//create a render func
	void run();


};

