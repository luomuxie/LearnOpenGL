#include "framebuffers.h"
#include <iostream>
#include <glad/glad.h>
#include "func.h"
#include <shader_s.h>
#include "Constants.h"

void framebuffers::initOpenGL()
{
	//init OpenGL
	glfwInit();
	//set the version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the OpenGL to use the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "framebuffers", NULL, NULL);
	//if the window is not created, then print the error
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;		
		glfwTerminate();
		//return -1;
	}

	//set the window to the main context
	glfwMakeContextCurrent(window);
	//set the frame buffer size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		//return -1;
	}
	//set the view port
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void framebuffers::initVertexs()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float cubeVertices[] = {
		// positions          // texture Coords
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
	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	//set the screen quad vertex attributes
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   // texCoords
			-1.0f,  1.0f,   0.0f, 1.0f,
			-1.0f, -1.0f,   0.0f, 0.0f,
			 1.0f, -1.0f,   1.0f, 0.0f,
	
			-1.0f,  1.0f,   0.0f, 1.0f,
			 1.0f, -1.0f,   1.0f, 0.0f,
			 1.0f,  1.0f,   1.0f, 1.0f
	};

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//set the vertex data
	//set the vao and vbo
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	//bind the vao and vbo
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	//set the data of vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	//set the vertex attribute
	//set the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//enable the vertex attribute
	glEnableVertexAttribArray(0);
	//set the texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));	
	glEnableVertexAttribArray(1);
	//unbind the vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//set the plane vertex data
	//set the vao and vbo
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	//bind the vao and vbo
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	//set the data of vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	//set the vertex attribute
	//set the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//set the texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable the vertex attribute	
	glEnableVertexAttribArray(1);
	//unbind the vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//set the screen quad vertex data
	//set the vao and vbo
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	//bind the vao and vbo
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	//set the data of vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	//set the vertex attribute
	//set the position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	//enable the vertex attribute
	glEnableVertexAttribArray(0);
	//set the texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	//enable the vertex attribute
	glEnableVertexAttribArray(1);
	//unbind the vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void framebuffers::initFramebuffers()
{
}

void framebuffers::run()
{
	initOpenGL();
	initVertexs();

	//init the shader
	Shader shader((SHADER_PATH + "frame_buffers.vs").c_str(), (SHADER_PATH + "frame_buffers.fs").c_str());
	Shader screenShader((SHADER_PATH + "frame_buffers_screen.vs").c_str(), (SHADER_PATH + "frame_buffers_screen.fs").c_str());

	//set the texture
	unsigned int cubeTexture = loadTexture((TEXTURE_PATH + "marble.jpg").c_str());
	unsigned int floorTexture = loadTexture((TEXTURE_PATH + "metal.png").c_str());

	//open depth test
	 glEnable(GL_DEPTH_TEST);

	 

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//process the input
		processInput(window);

		//set the color of the screen
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		//clear the color buffer and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set the view matrix
		glm::mat4 view = camera.GetViewMatrix();
		//set the projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
						0.1f, 100.0f);
		//set the model matrix
		glm::mat4 model = glm::mat4(1.0f);

		//set the shader
		shader.use();
		//set the uniform
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		//draw the cube
		glBindVertexArray(cubeVAO);
		//set the model matrix
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		//set the uniform
		shader.setMat4("model", model);
		//set the texture
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		//draw the cube
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//set the model matrix
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		//set the uniform
		shader.setMat4("model", model);
		//draw the cube
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//draw the floor
		glBindVertexArray(planeVAO);
		//set the model matrix
		model = glm::mat4(1.0f);
		//set the uniform
		shader.setMat4("model", model);
		//set the texture
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		//draw the floor
		glDrawArrays(GL_TRIANGLES, 0, 6);


		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}

	//close the window
	glfwTerminate();

}
