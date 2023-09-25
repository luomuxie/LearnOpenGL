#pragma once
#include <camera.h>
//create a class for the specular map by the file name
class lighting_maps_specular_map
{
	//create a func to init the openGL
	void initOpenGL();
	//create a window and the window size
	GLFWwindow* window;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	//create a func to set the vertex data
	void setVertexData();
	//create the cubvao, lightvao, vbo
	unsigned int cubeVAO, lightVAO, VBO;

	//create a func to init the shader
	void initShader();
	//create the lightshaderID
	unsigned int lightShaderID;
	//create the cubeshaderID
	unsigned int cubeShaderID;

	//create a func to process the input
	void processInputColor(GLFWwindow* window);
	//create deltaTime
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	//create a camera
	Camera camera = Camera(
		glm::vec3(3.7342, 2.0652f, -1.6181f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		144.3973f,
		-26.8f
	);

	//create a func to load the texture
	void loadTexture();

};

