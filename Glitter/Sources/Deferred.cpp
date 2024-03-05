#include "Deferred.h"
#include "model.h"
#include "Common/Renderer.cpp"
#include "Constants.h"



void Deferred::RenderModel(Shader &shader, Model& modelObj)
{
	//render the model by the objPos
	shader.use();
	//set the view and projection matrix
	shader.setMat4("projection", GetProjectionMatrix());
	shader.setMat4("view", GetViewMatrix());
	for (unsigned int i = 0; i < 9; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, objectPositions[i]);
		model = glm::scale(model, glm::vec3(0.25f));
		shader.setMat4("model", model);
		modelObj.Draw(shader);
	}
}

void Deferred::InitLightData()
{
				
	for (GLuint i = 0; i < NR_LIGHTS; i++)
	{
		// Calculate slightly random offsets
		GLfloat xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		GLfloat yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
		GLfloat zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
		// Also calculate random color
		GLfloat rColor = ((rand() % 100) / 200.0f) + 0.5; // Between 0.5 and 1.0
		GLfloat gColor = ((rand() % 100) / 200.0f) + 0.5; // Between 0.5 and 1.0
		GLfloat bColor = ((rand() % 100) / 200.0f) + 0.5; // Between 0.5 and 1.0
		lightColors.push_back(glm::vec3(rColor, gColor, bColor));
	}
}

void Deferred::Run()
{
	scale = 3;
	screenWidth = 800 * scale;
	screenHeight = 600 * scale;
	camera.Position = glm::vec3(0.0f, .0f, 40);
	camera.Zoom = 14;
	camera.Pitch = -80;

	

	
	InitWindow();
	//init the light data
	InitLightData();

	//create a model object	
	Model ourModel((MODEL_PATH + "nanosuit\\nanosuit.obj").c_str());
	Shader defferedGSahder = CreateShader("DeferredGSahder", "DeferredGSahder");



	Shader deferredQuadShader = CreateShader("DeferedQuadSahder", "DeferedQuadSahder");
	deferredQuadShader.use();
	deferredQuadShader.setInt("gPosition", 0);
	deferredQuadShader.setInt("gNormal", 1);
	deferredQuadShader.setInt("gAlbedoSpec", 2);

	//create a shader for light
	Shader lightShader = CreateShader("DeferredLight", "DeferredLight");



	//init the attachments array
	attachments = {
		// 存储位置的颜色缓冲
		Renderer::FramebufferAttachment(Renderer::FramebufferAttachment::Type::Color, GL_RGBA8, GL_RGBA, GL_FLOAT),
		// 存储法线颜色缓冲
		Renderer::FramebufferAttachment(Renderer::FramebufferAttachment::Type::Color, GL_RGB16F, GL_RGB, GL_FLOAT),
		// 存储颜色和镜面反射缓冲
		Renderer::FramebufferAttachment(Renderer::FramebufferAttachment::Type::Color, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE),
		//depth
		Renderer::FramebufferAttachment(Renderer::FramebufferAttachment::Type::Depth, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT)
	};

	//create a framebuffer
	gBuffer = Renderer::createFramebuffer(attachments, screenWidth, screenHeight);
	//open the depth test
	glEnable(GL_DEPTH_TEST);
	
	//main loop
	//check the window is not closed
	while (!glfwWindowShouldClose(window))
	{
		//record the time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;

		//input
		//process the input
		InputProcess(window);		
		//rotation the camera by the time by the radius,and always look at the center
		float camX = sin(glfwGetTime()) * 30;
		float camZ = cos(glfwGetTime()) * 30;
		camera.Position.x = camX;
		camera.Position.z = camZ;
		// 始终看向场景中心点
		camera.Front = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - camera.Position);
				

		//render
		//set the clear color
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.f, 0.0f, 1.0f);
		//clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use the gbuffer----------------------------------------------------
		glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render the model
		RenderModel(defferedGSahder, ourModel);

		//use the default framebuffer------------------------------------------
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render the quad
		deferredQuadShader.use();
		//bind the gbuffer
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, attachments[0].textureID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, attachments[1].textureID);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, attachments[2].textureID);

		//send the view pos to the shader
		deferredQuadShader.setVec3("viewPos", camera.Position);
		//set the light data
		for (GLuint i = 0; i < NR_LIGHTS; i++)
		{
			deferredQuadShader.setVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
			deferredQuadShader.setVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);

			const GLfloat constant = 1.0; // Note that we don't send this to the shader, we assume it is always 1.0 (in our case)
			const GLfloat linear = 0.7;
			const GLfloat quadratic = 1.8;

			deferredQuadShader.setFloat("lights[" + std::to_string(i) + "].Linear", linear);
			deferredQuadShader.setFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);			恨死了中国就我找到他们的那些方式把周慧现在的位置发了
		}
		//glDisable(GL_DEPTH_TEST);
				
		RenderQuad();		过去然后就时间的开始的当天下午工会就给我打电话了说是
		//render the light-----------------------------------------------------------------
		lightShader.use();
		lightShader.setMat4("projection", GetProjectionMatrix());
		lightShader.setMat4("view", GetViewMatrix());

		//copy depth buffer from gBuffer to default framebuffer
		glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Write to default framebuffer
		// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
		// The internal formats are implementation defined. This works on all of my systems, but if you require more consistency in your code, you might need to use FBOs.
		glBlitFramebuffer(0, 0, screenWidth, screenHeight, 0, 0, screenWidth, screenHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
		for (GLuint i = 0; i < NR_LIGHTS; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, lightPositions[i]);
			model = glm::scale(model, glm::vec3(0.15f));
			lightShader.setMat4("model", model);
			lightShader.setVec3("lightColor", lightColors[i]);
			RenderCube();
		}


		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	
	//exit the program
	glfwTerminate();
}
