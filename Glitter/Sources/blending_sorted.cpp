#include "blending_sorted.h"
#include <iostream>
#include <glad/glad.h>
#include "func.h"
#include <shader_s.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>

void blending_sorted::initOpenGL()
{
	//glwf init
	glfwInit();
	//set opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set opengl profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Blending Sorted", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		//release resource
		glfwTerminate();
		return;
	}
	//set current window
	glfwMakeContextCurrent(window);
	//set callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//set the callback function for the mouse with the window user pointer
	glfwSetWindowUserPointer(window, this);
	//set the callback function for the mouse with the lamd expression
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		blending_sorted* instance = static_cast<blending_sorted*>(glfwGetWindowUserPointer(window));
		instance->mouse_callback(xpos, ypos);
		});

	//set the callback function for the scroll
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		blending_sorted* instance = static_cast<blending_sorted*>(glfwGetWindowUserPointer(window));
		instance->scroll_callback(xoffset, yoffset);
		});
	
		
	//glad init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	//set viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

}

void blending_sorted::initVertexs()
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

	//cube vao
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	//cube vbo
	glGenBuffers(1, &cubeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	//set vertex attribute
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//texture coordinate
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//unbind vao
	glBindVertexArray(0);

	//plane vao
	glGenVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);
	//plane vbo
	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	//set vertex attribute
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//texture coordinate
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//unbind vao
	glBindVertexArray(0);
}

void blending_sorted::run()
{
	initOpenGL();
	initVertexs();
	
	//load the shader
	Shader shader("..\\Glitter\\Shaders\\stencil_testing.vs", "..\\Glitter\\Shaders\\stencil_testing.fs");

	//load the texture
	unsigned int cubeTexture = loadTexture("..\\Glitter\\resources\\textures\\marble.jpg");
	unsigned int floorTexture = loadTexture("..\\Glitter\\resources\\textures\\metal.png");

	//set texture unit
	shader.use();
	shader.setInt("texture1", 0);		

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//process input
		processInputs(window);

		//set the time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
 
		//render
		//clear the color buffer and depth buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the stencil buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		//set the projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
			0.1f, 100.0f);
		shader.setMat4(shader.PROJECTION, projection);

		//set the view matrix
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4(shader.VIEW, view);

		//draw the floor
		glBindVertexArray(planeVAO);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		//create the model matrix
		glm::mat4 model = glm::mat4(2.0f);

		shader.setMat4(shader.MODEL, model);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//draw the cube
		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);

		//set the model matrix
		model = glm::mat4(2.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		shader.setMat4(shader.MODEL, model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//swap buffer and poll the event
		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	//end the program
	glfwTerminate();
}

void blending_sorted::mouse_callback(double xposIn, double yposIn)
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

void blending_sorted::scroll_callback(double xoffset, double yoffset)
{
	//print the scroll offset
	std::cout << "xoffset: " << xoffset << " yoffset: " << yoffset << std::endl;

	//process the scroll
	camera.ProcessMouseScroll(yoffset);
}

void blending_sorted::processInputs(GLFWwindow* window)
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
