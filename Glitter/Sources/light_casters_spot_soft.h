#pragma once
#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
//create a class for the directional light
class light_casters_spot_soft
{
	//create a func to init the OpenGL
	void initOpenGL();
	//create a window and the window size
	GLFWwindow* window;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	//create a func to access the input
	void processInputColor(GLFWwindow* window);

	//create a func to set the vertex data
	void setVertexData();
	//create lightVAO,cubeVAO,VBO
	unsigned int lightVAO, cubeVAO, VBO;
	//create a func to init the shader
	void initShader();
	//create lightShader,objectShader
	unsigned int lightShaderID, cubeShaderID;

	//create a func to load the Map
	void loadMap();
	//create a camera
	//Camera camera = Camera(
	//	glm::vec3(3.7342, 2.0652f, -1.6181f),
	//	glm::vec3(0.0f, 1.0f, 0.0f),
	//	144.3973f,
	//	-26.8f
	//);
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 6.0f));
	//create a deltaTime
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//create the lightPos
	//glm::vec3 lightPos = glm::vec3(0.219188f, 8.9f, 3.0f);
	//create the lightPos
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, -9.77811f);

	//create the diffuseMapID
	unsigned int diffuseMapID;
	//create the specularMapID
	unsigned int specularMapID;

	//create a public func to run
public:
	void run();

};
