#pragma once
#include "Common/GraphicsWindowBase.h"
#include "model.h"
#include "Common/Renderer.cpp"
 //create a class called Deferred
class Deferred:public GraphicsWindowBase
{
	//create a array to store the model pos
	glm::vec3 objectPositions[9] = {
		glm::vec3(-3.0, -3.0, -3.0),
		glm::vec3(0.0, -3.0, -3.0),
		glm::vec3(3.0, -3.0, -3.0),
		glm::vec3(-3.0, -3.0, 0.0),
		glm::vec3(0.0, -3.0, 0.0),
		glm::vec3(3.0, -3.0, 0.0),
		glm::vec3(-3.0, -3.0, 3.0),
		glm::vec3(0.0, -3.0, 3.0),
		glm::vec3(3.0, -3.0, 3.0)
	};

	//create a func to render the model have two param shader and model
	void RenderModel(Shader &shader, Model& modelObj);

	//create a val to store gbufferID
	unsigned int gBuffer;
	//create attchments
	std::vector<Renderer::FramebufferAttachment> attachments;

	//create a func to init light data
	void InitLightData();

	//create a const for light num
	const GLuint NR_LIGHTS = 32;

	//create a val to store light pos
	std::vector<glm::vec3> lightPositions;
	//create a val to store light color
	std::vector<glm::vec3> lightColors;
	

public :
	void Run() override;
};