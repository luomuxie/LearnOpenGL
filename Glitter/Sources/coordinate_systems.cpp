#include "coordinate_systems.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void coordinate_systems::initOpenGL()
{
	//initiate the glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//set the openGL profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the openGL not resizable
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
	//initiate the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//set the viewport
	glViewport(0, 0, 800, 600);
}

void coordinate_systems::setVertexData()
{
	//create the rect's vertex data and the data of the color and the texture
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	//create the index data
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	//create the VAO, VBO, EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bing the VAO
	glBindVertexArray(VAO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the VBO's data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//bind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//set the EBO's data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//set the vertex attribute	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//set the vertex color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//set the vertex texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//unbind the VAO
	glBindVertexArray(0);
	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	//unbind the program
	glUseProgram(0);

}

void coordinate_systems::initShader()
{
	//init the shader with SmpleVertexShader.vert and SampleFragmentShader.frag
	Shader myshader = Shader("SampleVertexShader.vert", "SampleFragmentShader.frag");
	//use the shader
	myshader.use();
	//set the shaderID
	shaderID = myshader.ID;
}

void coordinate_systems::loadTexture()
{	
	//set the texture1
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//set the texture1's wrap and filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	//load the texture1's image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	//if the data is not null,then set the texture1's image
	if (data) {
		//set the texture1's image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,data);
		//generate the mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	//else print the error
	else {
		std::cout << "Failed to load texture1" << std::endl;
	}
	//free the data
	stbi_image_free(data);
}

void coordinate_systems::run()
{
	//set the vertex data
	setVertexData();
	//init the shader
	initShader();
	//load the texture
	loadTexture();
	
	//render loop
	while (!glfwWindowShouldClose(window)) {
		//process the input
		processInput(window);

		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////create the transform matrix
		//glm::mat4 transform = glm::mat4(1.0f);
		////set the transform matrix
		//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		//transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
		////get the transform matrix's location
		//unsigned int transformLoc = glGetUniformLocation(shaderID, "transform");
		////set the transform matrix
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		//create model matrix
		glm::mat4 model = glm::mat4(1.0f);
		//set the model matrix
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));

		//create view matrix
		glm::mat4 view = glm::mat4(1.0f);
		//set the view matrix
		view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f));
		//create projection matrix
		glm::mat4 projection = glm::mat4(1.0f);
		//set the projection matrix
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
		//get the model matrix's location
		unsigned int modelLoc = glGetUniformLocation(shaderID, "model");
		//set the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//get the view matrix's location
		unsigned int viewLoc = glGetUniformLocation(shaderID, "view");
		//set the view matrix
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//get the projection matrix's location
		unsigned int projectionLoc = glGetUniformLocation(shaderID, "projection");
		//set the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));










		//bind the texture
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		//use the shader
		glUseProgram(shaderID);						
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
}


