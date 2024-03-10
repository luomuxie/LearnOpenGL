#include "NeonHeart.h"

void NeonHeart::Run()
{
	//init opengl
	scale = 2;
	screenHeight = screenWidth = 600* scale;
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

		//start the imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		


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


		//const float hoff = 0.58;
		////const vec3 dbcol = HSV2RGB(vec3(hoff+0.96, 0.8, 0.75));

		////const vec3 fbcol = HSV2RGB(vec3(hoff+0.95, 0.7, 2.0));


		ImGui::NewFrame();
		{
			ImGui::Begin("NeonHeart");
			ImGui::Text("Welcome to NeonHeart");
			//create a color
			static float color[3] = { 1,0.06, 0 };
			ImGui::ColorEdit3("clear color", color);
			//send the color to the shader
			shader.setVec3("iHeartColor", glm::vec3(color[0], color[1], color[2]));

			//create a color for the heartEdge
			static float heartEdgeColor[3] = { 0.47, 0.094, 0.35 };
			ImGui::ColorEdit3("heartEdgeColor", heartEdgeColor);
			//send the color to the shader
			shader.setVec3("iHeartEdgeColor", glm::vec3(heartEdgeColor[0], heartEdgeColor[1], heartEdgeColor[2]));

			//创建一个下拉选择框，选择不同的noise type
			static int noiseType = 0;
			ImGui::Combo("NoiseType", &noiseType, "Perlin\0Simplex\0Generic");
			//send the noise type to the shader
			shader.setInt("iNoiseType", noiseType);


			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	EndProgram();
	
}
