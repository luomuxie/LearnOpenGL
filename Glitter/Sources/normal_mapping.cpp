#include "normal_mapping.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <camera.h>
#include "Common/GraphicsWindowBase.h"
#include "Common/InputUtil.h"
#include <shader_s.h>
#include "Constants.h"
#include "func.h"


void normal_mapping::initVertex()
{
	//create a plane vertex
	GLfloat planeVertices[] = {
		// Positions          // Texture Coords
		-1.0f,  1.0f, 0.0f,    0.0f, 1.0f, // Top Left
		 1.0f,  1.0f, 0.0f,    1.0f, 1.0f, // Top Right
		 1.0f, -1.0f, 0.0f,    1.0f, 0.0f, // Bottom Right

		-1.0f,  1.0f, 0.0f,    0.0f, 1.0f, // Top Left (repeated for the second triangle)
		-1.0f, -1.0f, 0.0f,    0.0f, 0.0f, // Bottom Left
		 1.0f, -1.0f, 0.0f,    1.0f, 0.0f  // Bottom Right (repeated for the second triangle)
	};

	//set plane vertex
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);

	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glBindVertexArray(0);
}

void normal_mapping::run()
{
	InitWindow();
	initVertex();

	Shader basicShader = CreateShader("normal_mapping", "normal_mapping");
	Shader lightCubeShader = CreateShader(BASIC_NORMAL_SHADER, BASIC_NORMAL_SHADER);
	

	//load texture
	unsigned int brickwall = LoadTexture("brickwall.jpg");
	unsigned int brickwall_normal = LoadTexture("brickwall_normal.jpg");

	//set texture
	basicShader.use();
	basicShader.setInt("ourTexture", 0);
	basicShader.setInt("normalMap", 1);

	// Light position
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);

	//enable depth test
	glEnable(GL_DEPTH_TEST);
   
	//main loop 
	while (!glfwWindowShouldClose(window))
	{		
		//record the time 
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		InputProcess(window);
		//clear the color buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//create light pos
		glm::vec3 lightPos = glm::vec3(0.5f, 1.0f, 0.3f);

		//rotation the light by time x ,y
		lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
		lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
		//create lightcuber
		lightCubeShader.use();
		lightCubeShader.setMat4(lightCubeShader.VIEW, GetViewMatrix());
		lightCubeShader.setMat4(lightCubeShader.PROJECTION, GetProjectionMatrix());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, brickwall);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f));
		lightCubeShader.setMat4(lightCubeShader.MODEL, model);		
		RenderCube();
		

		//draw the plane
		basicShader.use();		
		model = glm::mat4(1.0f);
		basicShader.setMat4(basicShader.VIEW, GetViewMatrix());
		basicShader.setMat4(basicShader.PROJECTION, GetProjectionMatrix());
		basicShader.setMat4(basicShader.MODEL, model);
		//set the light position
		basicShader.setVec3("lightPos", lightPos);
		//set the view position
		basicShader.setVec3("viewPos", camera.Position);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, brickwall);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, brickwall_normal);
		 
		//draw plane
		glBindVertexArray(planeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//swap the back buffer with the front buffer
		glfwSwapBuffers(window);
	}

	//terminte 
	glfwTerminate();	
}
