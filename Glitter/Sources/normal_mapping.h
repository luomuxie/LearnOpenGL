#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
#include "Common/GraphicsWindowBase.h"
//create a class by file name
class normal_mapping:public GraphicsWindowBase
{
	//create a func to init vertex
	void initVertex();
	//create  planevao and vbo
	GLuint planeVAO, planeVBO;

public:
	void run() override;
};
