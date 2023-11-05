#include "stencil_testing.h"
#include <iostream>
#include <glad/glad.h>
#include "func.h"
#include <shader_s.h>
#include <glitter.hpp>




void stencil_testing::initOpenGL()
{
	//init the OpenGL
	glfwInit();
	//set the version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the OpenGL to use the core-profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//enble the resize
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Stencil Testing", NULL, NULL);
	//judge if the window is created
	if (window == NULL)
	{
		//print the error
		std::cout << "Failed to create GLFW window" << std::endl;
		//end the program
		glfwTerminate();
		return;
	}

	// set the window to the current context
	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, this);
	//set the callback function for the resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//set the callback function for the mouse with the lamd expression
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		stencil_testing* instance = static_cast<stencil_testing*>(glfwGetWindowUserPointer(window));
		instance->mouse_callback(xpos, ypos);
		});


	//set the callback function for the scroll
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		stencil_testing* instance = static_cast<stencil_testing*>(glfwGetWindowUserPointer(window));
		instance->scroll_callback(xoffset, yoffset);
		});

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	
	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//print the error
		std::cout << "Failed to initialize GLAD" << std::endl;
		//end the program
		return;
	}
		
	//set the size of the viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void stencil_testing::initVertices()
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

	// cube VAO
	//unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//bind the cube VAO
	glBindVertexArray(cubeVAO);
	//bind the cube VBO
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	//set the cube VBO data
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	//set the vertex attribute pointer
	//set the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//enable the position attribute
	glEnableVertexAttribArray(0);
	//set the texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable the texture attribute
	glEnableVertexAttribArray(1);
	//unbind the cube VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the cube VAO
	glBindVertexArray(0);

	// plane VAO
	//unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	//bind the plane VAO
	glBindVertexArray(planeVAO);
	//bind the plane VBO
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	//set the plane VBO data
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	//set the vertex attribute pointer
	//set the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//enable the position attribute
	glEnableVertexAttribArray(0);
	//set the texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable the texture attribute
	glEnableVertexAttribArray(1);
	//unbind the plane VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the plane VAO
	glBindVertexArray(0);	
}

void stencil_testing::run()
{
	initOpenGL();
	initVertices();;
	//load the shader
	Shader shader("..\\Glitter\\Shaders\\stencil_testing.vs", "..\\Glitter\\Shaders\\stencil_testing.fs");
	//load the shader for plane
	Shader shaderSingleColor("..\\Glitter\\Shaders\\stencil_testing.vs", "..\\Glitter\\Shaders\\stencil_single_color.fs");

	//load the texture
	unsigned int cubeTexture = loadTexture("..\\Glitter\\Resources\\Textures\\container2.png");	
	unsigned int floorTexture = loadTexture("..\\Glitter\\Resources\\Textures\\metal.png");
	//set the shader
	shader.use();
	//set the shader for the texture the same as the texture number
	shader.setInt("ourTexture", 0);

	//configure  global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	glDepthFunc(GL_LESS);	
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		

	while (!glfwWindowShouldClose(window))
	{
		//set the time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//process the input
		processInput(window);
		//clear the color buffer and the depth buffer
		//enable the depth test
		//glEnable(GL_DEPTH_TEST);
		glClearColor(0.11f, 0.11f, 0.11f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);

		//set the shader
		shader.use();		
		glm::mat4 view = camera.GetViewMatrix();						
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
						0.1f, 100.0f);		
		shader.setMat4(shader.PROJECTION, projection);
		shader.setMat4(shader.VIEW, view);


		//draw the floor----------------------------------------------------------------------------
		//set the model matrix
		glm::mat4 model = glm::mat4(2.0f);		
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));		
		shader.setMat4(shader.MODEL, model);
		//
		glStencilMask(0x00);
		glBindVertexArray(planeVAO);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// 1st. render pass, draw objects as normal, writing to the stencil buffer
		// --------------------------------------------------------------------
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		
		// cubes
		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		shader.setMat4(shader.MODEL, model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setMat4(shader.MODEL, model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
		// Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing
		// the objects' size differences, making it look like borders.
		// --------------------------------------------------------------------
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		shaderSingleColor.use();
		shaderSingleColor.setMat4(shaderSingleColor.VIEW, view);
		shaderSingleColor.setMat4(shaderSingleColor.PROJECTION, projection);
		float scale = 1.1;

		//cubes's border
		glBindVertexArray(cubeVAO);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		shaderSingleColor.setMat4(shaderSingleColor.MODEL, model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		shaderSingleColor.setMat4(shaderSingleColor.MODEL, model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//reset the stencil test
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);

		
		//swap the buffer
		glfwSwapBuffers(window);
		//process the event
		glfwPollEvents();
				
	}
	//end the program
	glfwTerminate();
}


void stencil_testing::mouse_callback(double xposIn, double yposIn)
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

void stencil_testing::scroll_callback(double xoffset, double yoffset)
{
	//process the scroll
	camera.ProcessMouseScroll(yoffset);
}

void stencil_testing::processInput(GLFWwindow* window)
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
