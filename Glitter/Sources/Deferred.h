#pragma once
#include "Common/GraphicsWindowBase.h"
#include "model.h"
 //create a class called Deferred
class Deferred:public GraphicsWindowBase
{
	//create a array to store the model pos
	glm::vec3 objectPositions[10] = {
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
	





public :
	void Run() override;
};