#include "light_casters_point.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <stb_image.h>
#include <glm/gtc/type_ptr.hpp>

void light_casters_point::initOpenGL()
{
	//init the openGL
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL to use the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//enable the openGL sizeadjust
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "light_casters_directional", NULL, NULL);
	//judge if the window create successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}
	//tell the openGL to use this window
	glfwMakeContextCurrent(window);
	// set the callback function for the window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//tell the glad to load the openGL function point
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

		//return -1;
	}
	//set the openGL viewport position and size
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}



void light_casters_point::setVertexData()
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	//set the vertex data to cubeVAO	
	glGenVertexArrays(1, &cubeVAO);
	//set the vertex data to VBO
	glGenBuffers(1, &VBO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the vertex data to the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//bind the cubeVAO
	glBindVertexArray(cubeVAO);
	//set the vertex attribute
	//set the vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//enable the vertex position
	glEnableVertexAttribArray(0);
	//set the vertex normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable the vertex normal
	glEnableVertexAttribArray(1);
	//set the vertex texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//enable the vertex texture
	glEnableVertexAttribArray(2);

	//set the lightVAO
	glGenVertexArrays(1, &lightVAO);
	//bind the lightVAO
	glBindVertexArray(lightVAO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the vertex attribute
	//set the vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//enable the vertex position
	glEnableVertexAttribArray(0);

	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the cubeVAO
	glBindVertexArray(0);
	//unbind the lightVAO
	glBindVertexArray(0);
}

void light_casters_point::initShader()
{
	//create the shader object by using the shader source code
	Shader lightShader("..\\Glitter\\Shaders\\light.vs", "..\\Glitter\\Shaders\\light.fs");
	//active the shader program
	lightShader.use();
	//set the shader program
	lightShaderID = lightShader.ID;

	//create the cube shader object by using the shader source code
	Shader cubeShader("..\\Glitter\\Shaders\\light_casters_point.vs", "..\\Glitter\\Shaders\\light_casters_point.fs");
	//active the shader program
	cubeShader.use();
	//set the shader program
	cubeShaderID = cubeShader.ID;
}

void light_casters_point::loadMap()
{
	//load the diffuse map
	diffuseMapID = loadTexture("..\\Glitter\\Img\\container2.png");
	//load the specular map
	specularMapID = loadTexture("..\\Glitter\\Img\\container2_specular.png");
}

void light_casters_point::run()
{
	//init the openGL
	initOpenGL();
	setVertexData();
	initShader();
	loadMap();
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//main render loop
//judge if the window should close
	while (!glfwWindowShouldClose(window))
	{
		//calculate the delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//process the input
		processInputColor(window);
		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//active the light shader program
		glUseProgram(lightShaderID);
		//set the model matrix
		glm::mat4 model = glm::mat4(1.0f);
		//scale the model matrix
		model = glm::scale(model, glm::vec3(0.2f));
		//move the light position
		model = glm::translate(model, lightPos);

		float radius = 5.0f;
		float angle = glfwGetTime();
		lightPos.x = radius * cos(angle);
		lightPos.z = radius * sin(angle);

		
		//set the view matrix
		glm::mat4 view = camera.GetViewMatrix();
		//set the projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
			0.1f, 100.0f);
		//set the model matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//set the view matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//set the projection matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		//draw the light
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//cube---------------------------------------------------------------------------------
		//active the cube shader program
		glUseProgram(cubeShaderID);
		//set the model matrix
		model = glm::mat4(1.0f);
		//set the model matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//set the view matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//set the projection matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		//set the view position
		glUniform3fv(glGetUniformLocation(cubeShaderID, "viewPos"), 1, glm::value_ptr(camera.Position));

		//set the light properties		
		//set the light ambient
		glUniform3f(glGetUniformLocation(cubeShaderID, "light.ambient"), 0.2f, 0.2f, 0.2f);
		//set the light diffuse
		glUniform3f(glGetUniformLocation(cubeShaderID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		//set the light specular
		glUniform3f(glGetUniformLocation(cubeShaderID, "light.specular"), 1.0f, 1.0f, 1.0f);
		//set the light position
		glUniform3fv(glGetUniformLocation(cubeShaderID, "light.position"), 1, glm::value_ptr(lightPos));

		//set the light attenuation---------------------------------------------------------------
		//set the light constant
		glUniform1f(glGetUniformLocation(cubeShaderID, "light.constant"), 1.0f);
		//set the light linear
		glUniform1f(glGetUniformLocation(cubeShaderID, "light.linear"), 0.09f);
		//set the light quadratic
		glUniform1f(glGetUniformLocation(cubeShaderID, "light.quadratic"), 0.032f);

		//set the material properties
		//set the material shininess
		glUniform1f(glGetUniformLocation(cubeShaderID, "material.shininess"), 32.0f);
		////set the diffuse map
		glUniform1i(glGetUniformLocation(cubeShaderID, "material.diffuse"), 0);
		//set the specular map
		glUniform1i(glGetUniformLocation(cubeShaderID, "material.specular"), 1);
		//bind the diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMapID);
		//bind the specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMapID);

		//draw the cube
		//glBindVertexArray(cubeVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//open the depth test
		glEnable(GL_DEPTH_TEST);
		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
}

void light_casters_point::processInputColor(GLFWwindow* window)
{
	//judge if the user press the esc
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//tell the window to close
		glfwSetWindowShouldClose(window, true);
	}
	//judge if the user press the w
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//move the camera forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	//judge if the user press the s
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//move the camera backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	//judge if the user press the a
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//move the camera left
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	//judge if the user press the d
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//move the camera right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}
