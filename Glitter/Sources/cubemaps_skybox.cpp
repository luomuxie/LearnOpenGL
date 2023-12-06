#include "cubemaps_skybox.h"
#include <iostream>
#include"func.h"
#include <glad/glad.h>
#include <shader_s.h>
#include "Constants.h"

void cubemaps_skybox::initOpenGL()
{
	//init Opengl
	//init the glfw
	glfwInit();
	//set the version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the profile of opengl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window can be change
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//create the window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "cubemaps_skybox", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "create window failed" << std::endl;
		glfwTerminate();
		return;
	}

	//set the window to the current context
	glfwMakeContextCurrent(window);
	//set the callback function for the mouse with the window user pointer
	glfwSetWindowUserPointer(window, this);
	//set the callback function for the mouse with the lamd expression
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		cubemaps_skybox* instance = static_cast<cubemaps_skybox*>(glfwGetWindowUserPointer(window));
		instance->mouse_callback(xpos, ypos);
		});

	//set the callback function for the scroll
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		cubemaps_skybox* instance = static_cast<cubemaps_skybox*>(glfwGetWindowUserPointer(window));
		instance->scroll_callback(xoffset, yoffset);
		});

	//init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "init glad failed" << std::endl;
		return;
	}
	
	//set the callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	
	//set the viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

}
void cubemaps_skybox::mouse_callback(double xposIn, double yposIn)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//judge if the first mouse
		if (firstMouse)
		{
			//set the last x and y
			lastX = xposIn;
			lastY = yposIn;
			//set the first mouse to false
			firstMouse = false;
		}
		//calculate the offset of x and y	
		float xoffset = xposIn - lastX;
		float yoffset = lastY - yposIn;
		//set the last x and y
		lastX = xposIn;
		lastY = yposIn;
		//process the mouse movement
		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}
void cubemaps_skybox::scroll_callback(double xoffset, double yoffset)
{
	//process the scroll
	camera.ProcessMouseScroll(yoffset);
}

void cubemaps_skybox::initVertex()
{
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
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	//init the vao and vbo
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO);
	//bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	//set the data of vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	//set the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//set the texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the vao
	glBindVertexArray(0);

	//init the skybox vao and vbo
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(skyboxVAO);
	//bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	//set the data of vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	//set the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the vao
	glBindVertexArray(0);
	
}

void cubemaps_skybox::run()
{
	initOpenGL();
	initVertex();

	//create cube's shader
	Shader cubeShader((SHADER_PATH + "frame_buffers.vs").c_str(), (SHADER_PATH + "frame_buffers.fs").c_str());
	//load the texture
	unsigned int cubeTexture = loadTexture((TEXTURE_PATH + "container2.png").c_str());
	//create a string to store the path of the texture
	std::vector<std::string> faces
	{
		(TEXTURE_PATH + "skybox/right.jpg").c_str(),
		(TEXTURE_PATH + "skybox/left.jpg").c_str(),
		(TEXTURE_PATH + "skybox/top.jpg").c_str(),
		(TEXTURE_PATH + "skybox/bottom.jpg").c_str(),
		(TEXTURE_PATH + "skybox/front.jpg").c_str(),
		(TEXTURE_PATH + "skybox/back.jpg").c_str()
	};

	
	//create the cubemap texture
	unsigned int cubemapTexture = loadCubeTexture(faces);
	//create the skybox shader
	Shader skyboxShader((SHADER_PATH + "cubemaps_skybox.vs").c_str(), (SHADER_PATH + "cubemaps_skybox.fs").c_str());

	//set texture for the shader
	cubeShader.use();
	cubeShader.setInt("ourTexture", 0);
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	
	
	//open the depth test
	glEnable(GL_DEPTH_TEST);
	
	while (!glfwWindowShouldClose(window))
	{
		// Calculate the delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		//glDepthFunc(GL_LESS);
		// Process input
		processInputs(window);

		// Clear the color and depth buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set up view and projection matrices
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		
		glDepthMask(GL_FALSE);
		skyboxShader.use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // Remove translation from the view matrix
		skyboxShader.setMat4(skyboxShader.VIEW, view);
		skyboxShader.setMat4(skyboxShader.PROJECTION, projection);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glBindVertexArray(skyboxVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);						
		glDepthMask(GL_TRUE);
		
		// Draw the cube
		cubeShader.use();
		view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		cubeShader.setMat4(cubeShader.MODEL, model);
		cubeShader.setMat4(cubeShader.VIEW, view);
		cubeShader.setMat4(cubeShader.PROJECTION, projection);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
				

		//// Change depth function to GL_LEQUAL for drawing skybox
		//glDepthFunc(GL_LEQUAL);
		//skyboxShader.use();
		//view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // Remove translation from the view matrix
		//skyboxShader.setMat4(skyboxShader.VIEW, view);
		//skyboxShader.setMat4(skyboxShader.PROJECTION, projection);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		//glBindVertexArray(skyboxVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);				
		//// Reset depth function to default
		//glDepthFunc(GL_LESS);


		// Swap the buffer and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &skyboxVBO);

	glfwTerminate();

}


void cubemaps_skybox::processInputs(GLFWwindow* window)
{
//if the esc is pressed, the window will close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	//if the w is pressed, the camera will move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	//if the s is pressed, the camera will move back
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	//if the a is pressed, the camera will move left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	//if the d is pressed, the camera will move right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}
