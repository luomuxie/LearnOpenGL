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

	
	

	

	//to override the virtual function in the base class
public:
	void Run() override;

};

