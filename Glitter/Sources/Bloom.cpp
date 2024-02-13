#include "Bloom.h"

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

void Bloom::Run()
{
    scale = 4;
    screenHeight = 600 * scale;
    screenWidth = 800 * scale;
    InitWindow();
    woodTexture = LoadTexture("wood.png");
    containerTexture = LoadTexture("container2.png");

    //create shader
    Shader shader = CreateShader("Bloom", "Bloom");
    //create light shader
    Shader shaderLight = CreateShader("Bloom", "BloomLight");
    InitAllLightVal();

    
    
    //open the depth test
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        InputProcess(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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

        glfwPollEvents();        
        glfwSwapBuffers(window);
    }
}
