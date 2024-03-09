#include "NeonHeart.h"

void NeonHeart::Run()
{
	//init opengl
	scale = 1;
	screenHeight = screenWidth = 800* scale;
	InitWindow();

	//create shader
	Shader shader = CreateEffShader("Neonheart", "Neonheart");
	
	InitImgui();

	//create main loop
	while (!glfwWindowShouldClose(window))
	{
		//set the time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		//set the color of the window
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the window
		glClear(GL_COLOR_BUFFER_BIT);

		//set the shader
		shader.use();
		//set the time
		shader.setFloat("iTime", currentFrame);

		//set the iResolution
		//create a v2
		glm::vec2 resolution = glm::vec2(screenWidth, screenHeight);

		shader.setVec2("iResolution", resolution);				
		//create plane
		RenderQuad();

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	EndProgram();
	
}
