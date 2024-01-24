#pragma once
#include <GLFW/glfw3.h>
#include <camera.h>
#include "Common/GraphicsWindowBase.h"
//create a class by file name
class normal_mapping:public GraphicsWindowBase
{

public:
	void run() override;
};
