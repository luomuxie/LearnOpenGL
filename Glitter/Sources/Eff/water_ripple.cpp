#include "water_ripple.h"


void water_ripple::Run()
{
	//init opengl
	scale = 4;
	screenHeight = screenWidth = 800* scale;
	InitWindow();

	//create shader
	Shader shader = CreateEffShader("water_ripple", "water_ripple");
	//load a texture
	unsigned int texture = LoadTexture("mossy_pebbles.png");

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
		//set the texture 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		//create plane
		RenderQuad();


		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	//end the program
	glfwTerminate();
	

}
