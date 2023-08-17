#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "textures.h"
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <stb_image.h>

void textures::initOpenGL()
{
	//initiate the glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

void textures::setVertexData()
{
	//create the rect's vertex data and the data of the color and the texture
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	//create the indices
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};



		
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);	
	glGenBuffers(1, &EBO);

	//bind the VAO
	glBindVertexArray(VAO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//bind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//set the data of the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//set the data of the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//enable the vertex attribute
	glEnableVertexAttribArray(0);

	//set the color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable the color attribute
	glEnableVertexAttribArray(1);

	//set the texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//enable the texture attribute
	glEnableVertexAttribArray(2);


	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the VAO
	glBindVertexArray(0);
	//unbind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


void textures::run()
{
	//initiate the openGL
	initOpenGL();
	//set the vertex data
	setVertexData();
	//set the shader program
	//create shader program from the shader
	Shader myshader("..\\Glitter\\Shaders\\texture.vs", "..\\Glitter\\Shaders\\texture.fs");
	//use the shader program
	myshader.use();
	//set the uniform

	//set the texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//set the texture wrapping/filtering options (on the currently bound texture object)
	//set the texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//set the texture filtering
	//set the texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//set the texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//load the image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("..\\Glitter\\Img\\container.jpg", &width, &height, &nrChannels, 0);
	//if the data is null,then print the error
	if (data) {
		//generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//generate the texture
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	//free the image memory
	stbi_image_free(data);

	//render loop
	while (!glfwWindowShouldClose(window)) {
		//process the input
		processInput(window);

		//render
		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//bind the texture
		glBindTexture(GL_TEXTURE_2D, texture);

		//draw the rect
		glUseProgram(myshader.ID);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}

}
