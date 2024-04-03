#include "HeartHalo.h"

void HeartHalo::Run()
{
	//init opengl
	scale = 3;
	screenHeight *= scale;
	screenWidth *= scale;
	InitWindow();

	//create shader
	Shader shader = CreateEffShader("HeartHalo", "HeartHalo");

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

		shader.use();

		//set the time
		shader.setFloat("iTime", currentFrame);

		//set the iResolution
		//create a v2
		glm::vec2 resolution = glm::vec2(screenWidth, screenHeight);

		shader.setVec2("iResolution", resolution);

		//create plane
		RenderQuad();

		//start the imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("HeartHalo");
			ImGui::Text("Welcome to HeartHalo");

			//create a color
			static float color[3] = { 1,0.4, 0.3 };
			ImGui::ColorEdit3("heartColor", color);
			//send the color to the shader
			shader.setVec3("iHeartColor", glm::vec3(color[0], color[1], color[2]));

			//create a color for the heartBg
			static float heartBgColor[3] = { 1.0,0.8,0.7 };
			ImGui::ColorEdit3("heartBgColor", heartBgColor);
			//send the color to the shader
			shader.setVec3("iHeartBgColor", glm::vec3(heartBgColor[0], heartBgColor[1], heartBgColor[2]));

			//create a float val for the growThickness
			static float glowThickness = 0.01;
			ImGui::SliderFloat("glowThickness", &glowThickness, 0.01, 0.1);
			//send the val to the shader
			shader.setFloat("iGlowThickness", glowThickness);

			//create a float for the glow offset
			static float glowOffset = -1;
			ImGui::SliderFloat("glowOffset", &glowOffset, -1.0, 1.0);
			//send the val to the shader
			shader.setFloat("iGlowOffset", glowOffset);
			
				
			//end the imgui frame
			ImGui::End();
		}
		//render the imgui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the events
		glfwPollEvents();
	}

	EndProgram();

}
