#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Colors.h"
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
//include the camera header file
#include <camera.h>

void Colors::initOpenGL()
{
	//init the glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL to use the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create the window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
}

void Colors::setVertexData()
{
	//create a cube vertex data array 
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f,  0.5f, -0.5f,  
		 0.5f,  0.5f, -0.5f,  
		-0.5f,  0.5f, -0.5f,  
		-0.5f, -0.5f, -0.5f,  

		-0.5f, -0.5f,  0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  
		-0.5f, -0.5f,  0.5f,  

		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f,  
		-0.5f, -0.5f, -0.5f,  
		-0.5f, -0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  

		 0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  

		-0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f, -0.5f,  0.5f,  
		-0.5f, -0.5f,  0.5f,  
		-0.5f, -0.5f, -0.5f,  

		-0.5f,  0.5f, -0.5f,  
		 0.5f,  0.5f, -0.5f,  
		 0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f, -0.5f,  
	};

	//create a VAO
	//glGenVertexArrays(1, &VAO);
	////create a VBO
	//glGenBuffers(1, &VBO);
	////bind the VAO
	//glBindVertexArray(VAO);
	////bind the VBO
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	////set the VBO data
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	
	////set the vertex attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	////create light VAO
	//glGenVertexArrays(1, &lightVAO);
	////bind the light VAO
	//glBindVertexArray(lightVAO);
	////bind the VBO
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	////set the vertex attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//

	////enable the vertex attribute
	//glEnableVertexAttribArray(0);
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
}


void Colors::initShader()
{
	//create shader frome shader class
	Shader ourShader("..\\Glitter\\Shaders\\colors.vs", "..\\Glitter\\Shaders\\colors.fs");
	//use the shader
	ourShader.use();
	//set shaderID
	shaderID = ourShader.ID;

	//create light shader frome shader class
	Shader lightShader("..\\Glitter\\Shaders\\light.vs", "..\\Glitter\\Shaders\\light.fs");
	//use the shader
	lightShader.use();
	//set lightShaderID
	lightShaderID = lightShader.ID;
}

void Colors::run()
{
	//init the openGL
	initOpenGL();
	//set the vertex data
	setVertexData();
	//init the shader
	initShader();

	////create view matrix
	//glm::mat4 view = glm::mat4(1.0f);
	////set the view matrix
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//create projection matrix
	
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	glm::vec3 lightPos = glm::vec3(1.0f, 0.5f, 2.0f);
	//render loop
	while (!glfwWindowShouldClose(window)) {
		//process the input
		processInput(window);
		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		  								
		
		glm::mat4 projection = glm::mat4(1.0f);
		//set the projection matrix
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		//create view matrix
		glm::mat4 view = camera.GetViewMatrix();

		//create model matrix
		glm::mat4 model = glm::mat4(1.0f);
		//move the mmodel to lightPos
		//model = glm::translate(model, lightPos);
		//scale the model
		model = glm::scale(model, glm::vec3(0.2f));
		
		glUseProgram(lightShaderID);
		//set the model matrix for light
		glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//set the view matrix for light
		glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//set the projection matrix for light
		glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//glUseProgram(shaderID);
		////set the object color fo
		//glUniform3f(glGetUniformLocation(shaderID, "objectColor"), 1.0f, 0.5f, 0.31f);
		////set the light color
		//glUniform3f(glGetUniformLocation(shaderID, "lightColor"), 1.0f, 1.0f, 1.0f);
		////set the model matrix for cube
		//glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		////set the view matrix for cube
		//glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		////set the projection matrix for cube
		//glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));				

		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//draw the light
						
		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	//delete the VAO
	glDeleteVertexArrays(1, &VAO);
	//delete the VAO
	glDeleteVertexArrays(1, &lightVAO);
	//delete the VBO
	glDeleteBuffers(1, &VBO);
	
	//delete the window
	glfwTerminate();
}
