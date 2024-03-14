#include "NeonHeart.h"

void NeonHeart::Run()
{
	//init opengl
	scale = 2;
	screenHeight *= scale;
	screenWidth *= scale;
	InitWindow();

	//create shader
	Shader shader = CreateEffShader("Neonheart", "Neonheart2");
	
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

		//start the imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("NeonHeart");
			ImGui::Text("Welcome to NeonHeart");
			//create a color
			//vec3 hcol = vec3(1.0, 0.4 * r, 0.3) * s;
			static float color[3] = { 1,0.4, 0.3 };
			ImGui::ColorEdit3("clear color", color);
			//send the color to the shader
			shader.setVec3("iHeartColor", glm::vec3(color[0], color[1], color[2]));

			//vec3 bgCol = vec3(1.0,0.8,0.7-0.07*p.y)*(1.0-0.25*length(p));
			//create a color for the heartEdge
			static float heartEdgeColor[3] = { 1.0,0.8,0.7 };
			ImGui::ColorEdit3("heartBgColor", heartEdgeColor);
			//send the color to the shader
			shader.setVec3("iHeartBgColor", glm::vec3(heartEdgeColor[0], heartEdgeColor[1], heartEdgeColor[2]));

			//create a float for the noise offset
			static float noiseOffset = 0.085;
			ImGui::SliderFloat("noiseOffset", &noiseOffset, -1.0, 1.0);
			//send the noise offset to the shader
			shader.setFloat("iOffsetNoise", noiseOffset);

			
			//create a float for  offset the glow effect
			static float glowOffset = -0.047;
			ImGui::SliderFloat("glowOffset", &glowOffset, -1, 1.0);
			//send the glow offset to the shader
			shader.setFloat("iOffsetGlow", glowOffset);
		

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
