#include "Bloom.h"
#include <model.h>
#include "Constants.h"

void Bloom::RenderAllContainer(const Shader& shader)
{   
    //set the wood texture to the shader
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, woodTexture);

    //set the view and projection matrix
    shader.setMat4(shader.VIEW, GetViewMatrix());
    shader.setMat4(shader.PROJECTION, GetProjectionMatrix());

    glm::mat4 model = glm::mat4(1.0f);
    //translate the model
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
    model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
    shader.setMat4(shader.MODEL, model);
    RenderCube();

    glBindTexture(GL_TEXTURE_2D, containerTexture);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 1.0f, 1.0f));
    model = glm::scale(model, glm::vec3(0.5f));
    shader.setMat4(shader.MODEL, model);
    RenderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    shader.setMat4(shader.MODEL, model);
    RenderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
    model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(1.25));
    shader.setMat4("model", model);
    RenderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
    model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    shader.setMat4("model", model);
    RenderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader.setMat4("model", model);
    RenderCube();
}

void Bloom::RenderAllLight(const Shader& shader)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    //create a array of light color
    

    //create a loop to render the light
    for (unsigned int i = 0; i < lightPositions.size(); i++)
    {
		//shader.setVec3("lightPositions[" + std::to_string(i) + "]", lightPositions[i]);
		//shader.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

		// also set light source
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPositions[i]);
		model = glm::scale(model, glm::vec3(0.25f));
		shader.setMat4("model", model);
        //set the color of the light
        shader.setVec3("lightColor", lightColors[i]);
		RenderCube();
	}   

}

void Bloom::InitAllLightVal()
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

void Bloom::InitHDRBuffer()
{
    glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	// create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values)
	glGenTextures(2, colorBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// attach texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
	}
	// create and attach depth buffer (renderbuffer)
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth, screenHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);  
    //check the framebuffer
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        //print the error
        std::cout << "Framebuffer not complete!" << std::endl;
    }
    //unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Bloom::InitPingPongBuffer()
{
    glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
			std::cout << "Framebuffer not complete!" << std::endl;
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Bloom::InputProcess(GLFWwindow* window)
{
    //override the InputProcess function
    GraphicsWindowBase::InputProcess(window);
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
        if (exposure > 0.0f)
            exposure -= 0.001f;
        else
            exposure = 0.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        exposure += 0.001f;
    }
        
}



void Bloom::Run()
{
    scale = 4;
    screenHeight = 600 * scale;
    screenWidth = 800 * scale;
    //set camera up
    camera.Position = glm::vec3(-3 ,1, 7);
    InitWindow();
    InitHDRBuffer();
    InitPingPongBuffer();
    InitAllLightVal();

    woodTexture = LoadTexture("wood.png");
    containerTexture = LoadTexture("container2.png");

    //create shader
    Shader shader = CreateShader("Bloom", "Bloom");
    //create light shader
    Shader shaderLight = CreateShader("Bloom", "BloomLight");
    Shader shaderBlur = CreateShader("BloomBlur", "BloomBlur");

    //load the shader     
    Shader modelShader = CreateShader("dynamic_exploding_eff", "dynamic_exploding_eff");
    //use the model to load the model
    Model ourModel((MODEL_PATH + "nanosuit\\nanosuit.obj").c_str());

    //create shader for bloom final
    Shader shaderBloomFinal = CreateShader("BloomBlur", "BloomFinal");
    shaderBloomFinal.use();
    shaderBloomFinal.setInt("scene", 0);
    shaderBloomFinal.setInt("bloomBlur", 1);
       
    //open the depth test
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        InputProcess(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //render the scene to the floating point framebuffer------------------------------------------------------------
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        //set the projection matrix
        shader.setMat4("projection", GetProjectionMatrix());        
        shader.setMat4("view", GetViewMatrix());
        shader.setVec3("viewPos", camera.Position);
        //set lighting uniforms by the lights struct
        for (unsigned int i = 0; i < lightPositions.size(); i++)
        {
			shader.setVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
			shader.setVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
		}         

        RenderAllContainer(shader);

       shaderLight.use();
       shaderLight.setMat4("projection", GetProjectionMatrix());
       shaderLight.setMat4("view", GetViewMatrix());
       RenderAllLight(shaderLight);

       modelShader.use();
       modelShader.setMat4("projection", GetProjectionMatrix());
       modelShader.setMat4("view", GetViewMatrix());
       glm::mat4 model = glm::mat4(1.0f);
       model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -1));
       model = glm::scale(model, glm::vec3(0.2f));
       modelShader.setMat4("model", model);
       //set the time
       modelShader.setFloat("time", glfwGetTime());

       ourModel.Draw(modelShader);

       
       //blur bright fragments with two-pass Gaussian Blur----------------------------------------
       glBindFramebuffer(GL_FRAMEBUFFER, 0);
       bool horizontal = true, first_iteration = true;
       unsigned int amount = 20;
       shaderBlur.use();
       for (unsigned int i = 0; i < amount; i++)
       {
		   glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
		   shaderBlur.setInt("horizontal", horizontal);
		   glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
		   RenderQuad();
		   horizontal = !horizontal;
		   if (first_iteration)
			   first_iteration = false;
       }


       //now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
       glBindFramebuffer(GL_FRAMEBUFFER, 0);

       //then render quad with final screen texture
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       shaderBloomFinal.use();
       glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);

       glActiveTexture(GL_TEXTURE1);
       glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);       
       shaderBloomFinal.setInt("bloom", bloom);
       shaderBloomFinal.setFloat("exposure", exposure);
       RenderQuad();
       
       glfwPollEvents();        
       glfwSwapBuffers(window);
    }
    glfwTerminate();

}
