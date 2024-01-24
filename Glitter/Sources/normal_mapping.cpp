#include "normal_mapping.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <camera.h>
#include "func.h"
#include "InputUtil.h"
#include "Common/GraphicsWindowBase.h"

void normal_mapping::run()
{
	init_window();
	//main loop 
	while (!glfwWindowShouldClose(window))
	{
		//check if any event is triggered
		glfwPollEvents();

		InputUtility::processInput(window, camera, deltaTime);
		//clear the color buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//swap the back buffer with the front buffer
		glfwSwapBuffers(window);
	}

	//terminte 
	glfwTerminate();	
}
