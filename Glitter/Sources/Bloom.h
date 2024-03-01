#pragma once
#include "Common/GraphicsWindowBase.h"

//create a class that inherits from GraphicsWindowBase
class Bloom : public GraphicsWindowBase
{	
	//接收一个shader做为参数，然后根据shader来渲染所有的cube
	void RenderAllContainer(const Shader& shader);
	//创建一个渲染光源的函数，接收一个shader做为参数
	void RenderAllLight(const Shader& shader);
	
	//create container texture
	unsigned int containerTexture;
	//create wood texture
	unsigned int woodTexture;	

	//create a array of light position
	std::vector<glm::vec3> lightPositions;
	//create a array of light color
	std::vector<glm::vec3> lightColors;

	//create a func to init all the light
	void InitAllLightVal();	

	//create a func to init hdr buffer
	void InitHDRBuffer();
	//create a val to store the hdr buffer
	unsigned int hdrFBO;
	//a array of color buffer
	unsigned int colorBuffers[2];

	//create a func to init ping pong buffer
	void InitPingPongBuffer();
	//create a val to store the ping pong buffer
	unsigned int pingpongFBO[2];
	//create a array of color buffer
	unsigned int pingpongColorbuffers[2];

	//create a val to store the exposure
	float exposure = 0.5;
	//create a val to store the bloom
	bool bloom = true;
	//override the InputProcess function
	void InputProcess(GLFWwindow* window) override;

	//create a  val to store the bloomKeyPressed
	bool bloomKeyPressed = false;
	

	  
	//to override the virtual function in the base class
public:
	void Run() override;

};

