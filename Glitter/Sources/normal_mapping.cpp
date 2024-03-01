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
	//GLfloat planeVertices[] = {
	//	// Positions          // Texture Coords
	//	-1.0f,  1.0f, 0.0f,    0.0f, 1.0f, // Top Left
	//	 1.0f,  1.0f, 0.0f,    1.0f, 1.0f, // Top Right
	//	 1.0f, -1.0f, 0.0f,    1.0f, 0.0f, // Bottom Right

	//	-1.0f,  1.0f, 0.0f,    0.0f, 1.0f, // Top Left (repeated for the second triangle)
	//	-1.0f, -1.0f, 0.0f,    0.0f, 0.0f, // Bottom Left
	//	 1.0f, -1.0f, 0.0f,    1.0f, 0.0f  // Bottom Right (repeated for the second triangle)
	//};

	// positions
	glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
	glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
	glm::vec3 pos3(1.0f, -1.0f, 0.0f);
	glm::vec3 pos4(1.0f, 1.0f, 0.0f);
	// texture coordinates
	glm::vec2 uv1(0.0f, 1.0f);
	glm::vec2 uv2(0.0f, 0.0f);
	glm::vec2 uv3(1.0f, 0.0f);
	glm::vec2 uv4(1.0f, 1.0f);
	// normal vector
	glm::vec3 nm(0.0f, 0.0f, 1.0f);

	//calculate the tangent and bitangent
	//calculate the first triangle
	//----------
	glm::vec3 tangent1, bitangent1;
	//calculate the edge of the triangle
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	//calculate the delta uv
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	//calculate the tangent and bitangent
	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent1 = glm::normalize(tangent1);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent1 = glm::normalize(bitangent1);

	//calculate the second triangle
	//----------
	glm::vec3 tangent2, bitangent2;
	//calculate the edge of the triangle
	glm::vec3 edge3 = pos3 - pos1;
	glm::vec3 edge4 = pos4 - pos1;
	//calculate the delta uv
	glm::vec2 deltaUV3 = uv3 - uv1;
	glm::vec2 deltaUV4 = uv4 - uv1;

	//calculate the tangent and bitangent
	f = 1.0f / (deltaUV3.x * deltaUV4.y - deltaUV4.x * deltaUV3.y);
	tangent2.x = f * (deltaUV4.y * edge3.x - deltaUV3.y * edge4.x);
	tangent2.y = f * (deltaUV4.y * edge3.y - deltaUV3.y * edge4.y);
	tangent2.z = f * (deltaUV4.y * edge3.z - deltaUV3.y * edge4.z);
	tangent2 = glm::normalize(tangent2);

	bitangent2.x = f * (-deltaUV4.x * edge3.x + deltaUV3.x * edge4.x);
	bitangent2.y = f * (-deltaUV4.x * edge3.y + deltaUV3.x * edge4.y);
	bitangent2.z = f * (-deltaUV4.x * edge3.z + deltaUV3.x * edge4.z);
	bitangent2 = glm::normalize(bitangent2);

	//set the plane vertex
	GLfloat planeVertices[] = {
		// Positions          // Normal           // TexCoords  // Tangent                          // Bitangent
		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
	};

	//set plane vertex
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);

	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);

	//set the position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
	//set the normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
	//set the texture attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));

	//set the tangent attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
	//set the bitangent attribute
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));

	glBindVertexArray(0);

}

void normal_mapping::Run()
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
		//rotation the plane by x with 90 degree
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f,0.0f,0.0f));

		//move the plane to the bottom
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));

		basicShader.setMat4(basicShader.VIEW, GetViewMatrix());
		basicShader.setMat4(basicShader.PROJECTION, GetProjectionMatrix());
		basicShader.setMat4(basicShader.MODEL, model);
		//set the light position
		//set the view position
		basicShader.setVec3("lightPos", lightPos);
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
