#include "BloomEff.h"
#include "model.h"
#include "Constants.h"

void BloomEff::RenderAllContainer(const Shader& shader)
{
	//set the wood texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, woodTexture);

	//set the view and projection matrix
	shader.setMat4(shader.VIEW, GetViewMatrix());
	shader.setMat4(shader.PROJECTION, GetProjectionMatrix());

	//set the floor
	//set the model matrix
	glm::mat4 model = glm::mat4(1.0f);
	//translate the model matrix
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
	//scale the model matrix
	model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
	//set the model matrix
	shader.setMat4(shader.MODEL, model);
	//render the cube
	RenderCube();

	//set the container
	//set the container texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, containerTexture);
	//set the model matrix
	model = glm::mat4(1.0f);
	//translate the model matrix
	model = glm::translate(model, glm::vec3(2.0f, 1.0f, 1.0));
	//scale the model matrix
	model = glm::scale(model, glm::vec3(0.5f));
	//set the model matrix
	shader.setMat4(shader.MODEL, model);
	//render the cube
	RenderCube();

	//set the model matrix
	model = glm::mat4(1.0f);
	//translate the model matrix
	model = glm::translate(model, glm::vec3(-1.0f, 1.0f, 2.0));
	//rotate the model matrix
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	//set the model matrix
	shader.setMat4(shader.MODEL, model);
	//render the cube
	RenderCube();

	//set the model matrix
	model = glm::mat4(1.0f);
	//translate the model matrix
	model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
	//rotate the model matrix
	model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	//scale the model matrix
	model = glm::scale(model, glm::vec3(1.25));
	//set the model matrix
	shader.setMat4(shader.MODEL, model);
	//render the cube
	RenderCube();


	//set the model matrix
	model = glm::mat4(1.0f);
	//translate the model matrix
	model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
	//rotate the model matrix
	model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	//set the model matrix
	shader.setMat4(shader.MODEL, model);
	//render the cube
	RenderCube();

	//set the model matrix
	model = glm::mat4(1.0f);
	//translate the model matrix
	model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
	//scale the model matrix
	model = glm::scale(model, glm::vec3(0.5));
	//set the model matrix
	shader.setMat4(shader.MODEL, model);
	//render the cube
	RenderCube();

}

void BloomEff::RenderAllLight(const Shader& shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, woodTexture);

	//create a loop to render the light
	for (int i = 0; i < lightPositions.size(); i++)
	{
		//set the model matrix
		glm::mat4 model = glm::mat4(1.0f);
		//translate the model matrix
		model = glm::translate(model, lightPositions[i]);
		//scale the model matrix
		model = glm::scale(model, glm::vec3(0.25f));
		//set the model matrix
		shader.setMat4(shader.MODEL, model);
		//set the view matrix
		shader.setMat4(shader.VIEW, GetViewMatrix());
		//set the projection matrix
		shader.setMat4(shader.PROJECTION, GetProjectionMatrix());

		//set the light color
		shader.setVec3("lightColor", lightColors[i]);
		//render the cube
		RenderCube();
	}
}

void BloomEff::InitAllLightVal()
{

	lightColors.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
	lightColors.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
	lightColors.push_back(glm::vec3(0.0f, 0.0f, 15.0f));
	lightColors.push_back(glm::vec3(0.0f, 5.0f, 0.0f));


	lightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f));
	lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
	lightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
	lightPositions.push_back(glm::vec3(-.8f, 2.4f, -1.0f));

}

void BloomEff::InitHDRBuffer()
{
	//create the framebuffer
	glGenFramebuffers(1, &hdrFBO);
	//create the texture
	glGenTextures(2, colorBuffers);
	//bind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	//create the color buffer
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//attach the texture to the framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
	}
	//create the depth buffer
	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth, screenHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	//create a array of draw buffer
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
	//check the framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	//unbind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BloomEff::InitPingPongBuffer()
{
	//create the framebuffer
	glGenFramebuffers(2, pingpongFBO);
	//create the texture
	glGenTextures(2, pingpongColorbuffers);
	//create the texture
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//attach the texture to the framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
		//check the framebuffer
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}
	//unbind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void BloomEff::InputProcess(GLFWwindow* window)
{
	//call the base class function
	GraphicsWindowBase::InputProcess(window);
	//if the key is pressed
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !bloomKeyPressed)
	{
		bloom = !bloom;
		bloomKeyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		bloomKeyPressed = false;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		exposure -= 0.01;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		exposure += 0.01;
	}
}

void BloomEff::Run()
{
	//init the windo
	scale = 4;
	screenHeight = 600 * scale;
	screenWidth = 800 * scale;
	camera.Position = glm::vec3(-3, 1, 7);

	InitWindow();
	InitAllLightVal();
	InitHDRBuffer();
	InitPingPongBuffer();

	//create shader for the container
	//Shader bloomEff("bloomEff.vs", "bloomEff.fs");
	Shader bloomShader = CreateShader("bloomEff", "bloomEff");

	//create light shader
	Shader lightShader = CreateShader("bloomEff", "bloomEffLight");

	//create the finalShader
	Shader finalShader = CreateShader("bloomEffFinal", "bloomEffFinal");
	finalShader.use();
	finalShader.setInt("scene", 0);
	finalShader.setInt("bloomBlur", 1);


	//create the blur shader
	Shader blurShader = CreateShader("bloomEffBlur", "bloomEffBlur");


	//load texture
	containerTexture = LoadTexture("container2.png");
	woodTexture = LoadTexture("wood.png");

	//load the model
	Model ourModel((MODEL_PATH + "nanosuit\\nanosuit.obj").c_str());
	//create the model shader
	Shader modelShader = CreateShader("bloomEffModel", "bloomEffModel");
	


	//open the depth test
	glEnable(GL_DEPTH_TEST);
	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//record the time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//set the clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//input process
		InputProcess(window);


		//bind the hdr buffer---------------------------------------------------------------
		glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		//render the scene
		bloomShader.use();
		//set the lighting uniform by the light struct
		for (unsigned int i = 0; i < lightPositions.size(); i++) {
			bloomShader.setVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
			bloomShader.setVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
		}
		RenderAllContainer(bloomShader);

		lightShader.use();		

		RenderAllLight(lightShader);

		modelShader.use();
		//set the view matrix
		modelShader.setMat4(modelShader.VIEW, GetViewMatrix());
		//set the projection matrix
		modelShader.setMat4(modelShader.PROJECTION, GetProjectionMatrix());
		//set the model matrix
		glm::mat4 model = glm::mat4(1.0f);
		//translate the model matrix
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -1.0f));
		//scale the model matrix
		model = glm::scale(model, glm::vec3(0.2f));
		//set the model matrix
		modelShader.setMat4(modelShader.MODEL, model);
		//set the time
		modelShader.setFloat("time", glfwGetTime());

		//render the model
		ourModel.Draw(modelShader);

		//blur the bright part---------------------------------------------------------------
		//bind the pingpong buffer
		bool horizontal = true, first_iteration = true;
		unsigned int amount = 10;
		blurShader.use();
		for (unsigned int i = 0; i < amount; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
			blurShader.setInt("horizontal", horizontal);
			glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
			RenderQuad();
			horizontal = !horizontal;
			if (first_iteration)
				first_iteration = false;
		}

		
		//unbind the hdr buffer---------------------------------------------------------
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//render the final effect---------------------------------------------------------
		finalShader.use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
		finalShader.setInt("bloom", bloom);
		finalShader.setFloat("exposure", exposure);
		
		//render a quad
		RenderQuad();

		glfwSwapBuffers(window);
		//poll event
		glfwPollEvents();
	}
	//end the window
	glfwTerminate();
}
