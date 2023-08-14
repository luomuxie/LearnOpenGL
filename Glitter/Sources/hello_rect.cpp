#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "hello_rect.h"
#include <iostream>
#include "func.h"
#include "hello_triangle.h"

//create a function to draw the rect with func
void hello_rect::hello_rectOpenGL() {
	//initiate the openGL
	initOpenGL();
	//initiate the shader
	initShader();
	//set up the vertex data
	setVertexData();
	//render loop
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);
		//render
		//clear the color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//draw the rect
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//the second argument is the number of indices,and the third argument is the type of the indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	//delete the vertex array object
	glDeleteVertexArrays(1, &VAO);
	//delete the vertex buffer object
	glDeleteBuffers(1, &VBO);
	//terminate the openGL
	glfwTerminate();
}

//create a function to initOpenGL
void hello_rect::initOpenGL() {
	//initiate the glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create the window
	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//check if the window is created
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	//set the context of the window
	glfwMakeContextCurrent(window);
	//set the callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//initiate the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;

	}
}

//create a function to set the vertex data
void hello_rect::setVertexData() {
	//create the vertex data
	float vertices[] = {
		//first triangle
		0.5f, 0.5f, 0.0f, //top right
		0.5f, -0.5f, 0.0f, //bottom right
		-0.5f, 0.5f, 0.0f, //top left
		//second triangle
		-0.5f, -0.5f, 0.0f, //bottom left
	};
	//create the indices
	unsigned int indices[] = {
		0, 1, 2, //first triangle
		1, 2, 3 //second triangle
	};

	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind the VAO
	glBindVertexArray(VAO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//bind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set the vertex attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	//enable the vertex attribute pointer
	glEnableVertexAttribArray(0);
	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the VAO
	glBindVertexArray(0);
	//unbind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


//create a function to init the shader
void hello_rect::initShader() {
	//create the vertex shader source code
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main(){\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	//create the fragment shader source code
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	//create the vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//compile the vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check if the vertex shader is compiled successfully
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if the vertex shader is not compiled successfully, print the error message
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX:COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//create the fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//compile the fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check if the fragment shader is compiled successfully
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if the fragment shader is not compiled successfully, print the error message
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//create the shader program
	shaderProgram = glCreateProgram();
	//attach the vertex shader and fragment shader to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//link the shader program
	glLinkProgram(shaderProgram);
	//check if the shader program is linked successfully
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if the shader program is not linked successfully, print the error message
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}
	//delete the vertex shader and fragment shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
