#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders_uniform.h"
#include <iostream>
#include "func.h"

void shaders_uniform::shaders_uniformOpenGL()
{
	//initiate the openGL
	initOpenGL();
	//set the vertex data
	setVertexData();
	//initiate the shader
	initShader();
	//render loop
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);
		//rendering commands here
		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);
		//use the shader program
		glUseProgram(shaderProgram);
		//update the uniform color
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//get the uniform location
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//set the uniform
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		//draw the triangle
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//delete the shader program
	glDeleteProgram(shaderProgram);
	//delete the VAO
	glDeleteVertexArrays(1, &VAO);
	//delete the VBO
	glDeleteBuffers(1, &VBO);
	//delete the EBO
	glDeleteBuffers(1, &EBO);
	//terminate the glfw
	glfwTerminate();
	return;
}

//create a function to init OpenGL in this class
void shaders_uniform::initOpenGL()
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
}

void shaders_uniform::setVertexData()
{
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
	//copy the vertices data into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//bind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//copy the indices data into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//set the vertex attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//enable the vertex attribute array
	glEnableVertexAttribArray(0);
	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the VAO
	glBindVertexArray(0);
	//unbind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void shaders_uniform::initShader()
{
	//create the vertex shader source code
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n" //the position variable has attribute position 0
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" //see how we directly give a vec3 to vec4's constructor
		"}\0";
	//create the fragment shader source code
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n" //the output variable of the fragment shader
		"uniform vec4 ourColor;\n" //we set the uniform in the OpenGL code
		"void main()\n"
		"{\n"
		"	FragColor = ourColor;\n" //set the output variable to a dark-red color
		"}\n\0";



	//create the vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//compile the vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check if the vertex shader is compiled
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if the vertex shader is not compiled,then print the error
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:VERTEX:COMPILATION_FAILED\n" << infoLog << std::endl;

	}
	//create the fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//compile the fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check if the fragment shader is compiled
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if the fragment shader is not compiled,then print the error
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;

	}
	//create the shader program
	shaderProgram = glCreateProgram();
	//attach the vertex shader and fragment shader to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//link the shader program
	glLinkProgram(shaderProgram);
	//check if the shader program is linked
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if the shader program is not linked,then print the error
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:PROGRAM:LINKING_FAILED\n" << infoLog << std::endl;

	}
	//delete the vertex shader and fragment shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


