#include "light_multiple.h"
#include <camera.h>
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <glm/gtc/type_ptr.hpp>


void light_multiple::initOpenGL()
{
	//init the glfw
	glfwInit();
	//set the version of the glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the profile of the glfw
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//enable the resize
	glfwWindowHint(GLFW_RESIZABLE, false);
	//create the window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "light_multiple", NULL, NULL);
	//if the window is not created
	if (window == NULL)
	{
		//print the error
		std::cout << "Failed to create the GLFW window" << std::endl;
		//exit the program
		glfwTerminate();
		return;
	}
	//set the context of the window
	glfwMakeContextCurrent(window);
	//set the framebuffer size func
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//print the error
		std::cout << "Failed to init GLAD" << std::endl;
		//exit the program
		return;
	}
	//set the viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

}

void light_multiple::processInputColor(GLFWwindow* window)
{
	//if the user press the esc
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//close the window
		glfwSetWindowShouldClose(window, true);
	}
	//if the user press the W
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//move the camera forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	//if the user press the S
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//move the camera backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	//if the user press the A
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//move the camera left
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	//if the user press the D
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//move the camera right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void light_multiple::setVertexData()
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
	//set lightcube data--------------------------------------------
	//create a VAO
	glGenVertexArrays(1, &lightVAO);
	//create a VBO
	glGenBuffers(1, &VBO);	
	//bind the VAO
	glBindVertexArray(lightVAO);
	 //bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the data of the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//set the position attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//enable the position attribute pointers
	glEnableVertexAttribArray(0);	
	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the VAO
	glBindVertexArray(0);

	//set cube data-----------------------------------------------
	//create a VAO
	glGenVertexArrays(1, &cubeVAO);
	//create a VBO
	glGenBuffers(1, &VBO);
	//bind the VAO
	glBindVertexArray(cubeVAO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the data of the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//set the position attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//enable the position attribute pointers
	glEnableVertexAttribArray(0);
	//set the normal attribute pointers
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable the normal attribute pointers
	glEnableVertexAttribArray(1);
	//set the texture attribute pointers
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//enable the texture attribute pointers
	glEnableVertexAttribArray(2);
	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the VAO
	glBindVertexArray(0);	

}

void light_multiple::initShader()
{
	//create the shader object by using the shader source code
	Shader lightShader("..\\Glitter\\Shaders\\light.vs", "..\\Glitter\\Shaders\\light.fs");
	//active the shader program
	lightShader.use();
	//set the shader program
	lightShaderID = lightShader.ID;

	//create the cube shader object by using the shader source code
	Shader cubeShader("..\\Glitter\\Shaders\\light_casters_spot_soft.vs", "..\\Glitter\\Shaders\\light_casters_spot_soft.fs");
	//active the shader program
	cubeShader.use();
	//set the shader program
	cubeShaderID = cubeShader.ID;
			
}

void light_multiple::loadMap()
{
	//load the diffuse map
	diffuseMapID = loadTexture("..\\Glitter\\Img\\container2.png");
	//load the specular map
	specularMapID = loadTexture("..\\Glitter\\Img\\container2_specular.png");	
}

void light_multiple::run()
{
	//init the OpenGL
	initOpenGL();
	//set the vertex data
	setVertexData();
	//init the shader
	initShader();
	//load the map
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
	//set the render loop if the window should not close
	while (!glfwWindowShouldClose(window)){
		//calculate the delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//process the input
		processInputColor(window);

		//set the background color
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the color buffer bit and depth buffer bit
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw the light cube---------------------------------------------------
		//active the lightShader program
		glUseProgram(lightShaderID);
		//set the model matrix
		glm::mat4 model = glm::mat4(1.0f);
		//set the scale matrix
		model = glm::scale(model, glm::vec3(0.2f));
		//set the translate matrix
		model = glm::translate(model, lightPos);

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
		//draw the light cube
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//draw the cube--------------------------------------------------------
		//active the cubeShader program
		glUseProgram(cubeShaderID);
		//set the view matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//set the projection matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		//set the light's attributes
		glUniform3fv(glGetUniformLocation(cubeShaderID, "light.position"), 1, glm::value_ptr(camera.Position));
		glUniform3f(glGetUniformLocation(cubeShaderID, "light.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
		//set the light's ambient
		glUniform3f(glGetUniformLocation(cubeShaderID, "light.ambient"), 0.2f, 0.2f, 0.2f);
		//set the light's diffuse
		glUniform3f(glGetUniformLocation(cubeShaderID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		//set the light's specular
		glUniform3f(glGetUniformLocation(cubeShaderID, "light.specular"), 1.0f, 1.0f, 1.0f);
		//set the light's cutOff
		glUniform1f(glGetUniformLocation(cubeShaderID, "light.cutOff"), glm::cos(glm::radians(12.5f)));
		//set the light's outerCutOff
		glUniform1f(glGetUniformLocation(cubeShaderID, "light.outerCutOff"), glm::cos(glm::radians(17.5f)));

		//set the material's shininess
		glUniform1f(glGetUniformLocation(cubeShaderID, "material.shininess"), 32.0f);
		//set the material's diffuse
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMapID);
		glUniform1i(glGetUniformLocation(cubeShaderID, "material.diffuse"), 0);
		//set the material's specular
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMapID);
		glUniform1i(glGetUniformLocation(cubeShaderID, "material.specular"), 1);

		//set the viewPos
		glUniform3f(glGetUniformLocation(cubeShaderID, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		//draw the cube
		//glBindVertexArray(cubeVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//set the model matrix in the draw loop
		for (unsigned int i = 0; i < 10; i++)
		{
			//set the model matrix
			glm::mat4 model = glm::mat4(1.0f);
			//set the translate matrix
			model = glm::translate(model, cubePositions[i]);
			//set the rotate matrix
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			//set the model matrix uniform
			glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			//draw the cube
			glBindVertexArray(cubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

							
		//enable the depth test
		glEnable(GL_DEPTH_TEST);
		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();

	}
	

}
