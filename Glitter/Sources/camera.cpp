#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "camera.h"
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <stb_image.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

void camera::initOpenGL()
{
	//init the GLFW
	glfwInit();
	//set the version of openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL to use the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//set the window not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create the window
	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//if the window is null,then print the error
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	//set the current context
	glfwMakeContextCurrent(window);
	//set the callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//set the viewport
	glViewport(0, 0, 800, 600);
	
}

void camera::setVertexData()
{
	//create a cube vertex data array 
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//create a cube vertex buffer object
	//generate the vertex buffer object
	glGenBuffers(1, &VBO);
	//bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//copy the vertex data to the vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//create a vertex array object
	//generate the vertex array object
	glGenVertexArrays(1, &VAO);
	//bind the vertex array object
	glBindVertexArray(VAO);
	//configure the vertex attribute pointers
	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//enable the vertex attribute
	glEnableVertexAttribArray(0);
	//texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	//enable the vertex attribute
	glEnableVertexAttribArray(1);

	//open depth
	glEnable(GL_DEPTH_TEST);

	//unbind the VAO
	glBindVertexArray(0);
	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the element buffer object
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//unbind the program
	glUseProgram(0);
}

void camera::setTextureData()
{	
	//generate the texture
	glGenTextures(1, &texture);
	//bind the texture
	glBindTexture(GL_TEXTURE_2D, texture);
	//set the texture wrapping/filtering options (on the currently bound texture object)
	//set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//set texture filtering to GL_LINEAR (usually basic linear blending)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//load image, create texture and generate mipmaps
	int width, height, nrChannels;
	//load the image data
	unsigned char* data = stbi_load("..\\Glitter\\Img\\container.jpg", &width, &height, &nrChannels, 0);
	//check if the data is loaded
	if (data)
	{
		//generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);	//generate the texture
		glGenerateMipmap(GL_TEXTURE_2D);	//generate the mipmaps
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//free the image memory
	stbi_image_free(data);	
}

void camera::setShaderData()
{
	//create the shader
	Shader ourShader("..\\Glitter\\Shaders\\coordinate.vs", "..\\Glitter\\Shaders\\coordinate.fs");
	//use the shader
	ourShader.use();
	shaderID = ourShader.ID;
}

void camera::run()
{
	//initialize opengl
	initOpenGL();
	//set the shader data
	setShaderData();
	//set the texture data
	setTextureData();
	//set the vertex data
	setVertexData();


	//create view matrix
	glm::mat4 view = glm::mat4(1.0f);
	//set the view matrix
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//create projection matrix
	glm::mat4 projection = glm::mat4(1.0f);
	//set the projection matrix
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	
	
	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//process input
		processInput(window);
		//set the clear color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer bit
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//bind the texture
		glBindTexture(GL_TEXTURE_2D, texture);
		//use the shader
		glUseProgram(shaderID);
		

		//set the projection matrix
		glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		//bind the vertex array object
		glBindVertexArray(VAO);

		//create cube positions
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(2.0f,5.0f,-15.0f),
			glm::vec3(-1.5f,-2.2f,-2.5f),
			glm::vec3(-3.8f,-2.0f,-12.3f),
			glm::vec3(2.4f,-0.4f,-3.5f),
			glm::vec3(-1.7f,3.0f,-7.5f),
			glm::vec3(1.3f,-2.0f,-2.5f),
			glm::vec3(1.5f,2.0f,-2.5f),
			glm::vec3(1.5f,0.2f,-1.5f),
			glm::vec3(-1.3f,1.0f,-1.5f)
		};

		//create camera position
		//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		//create camera target
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		//create camera up vector
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		

		//create a for loop to draw the cubes
		for (unsigned int i = 0; i < 10; i++)
		{
			//create the model matrix
			glm::mat4 model = glm::mat4(1.0f);
			//set the model matrix
			model = glm::translate(model, cubePositions[i]);
			//set the model matrix
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			//set the model matrix			
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			
			//set the view matrix
			//make the camera rotate around the cube
			float radius = 10.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
			//set the view matrix
			view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), cameraTarget, cameraUp);
			//set the view matrix
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));						

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//draw the triangles
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//unbind the vertex array object
		glBindVertexArray(0);
		//swap the buffers
		glfwSwapBuffers(window);
		//poll the events
		glfwPollEvents();
	}		
}



