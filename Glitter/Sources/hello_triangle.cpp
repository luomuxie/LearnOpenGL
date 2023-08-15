#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "hello_triangle.h"
#include <iostream>
#include "func.h"


//create a function to draw the triangle with func
void hello_triangle::hello_triangleOpenGL() {
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
		//draw the triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
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


//create a function to initShader
void hello_triangle::initShader() {
	//initiate the vertex shader
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n" // the position variable has attribute position 0
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // see how we directly give a vec3 to vec4's constructor
		"}\0";
	//initiate the fragment shader
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // set the color of the fragment
		"}\n\0";

	//initiate openGL
	//create a vertex shader object
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach the shader source code to the shader object and compile the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check if the shader compile success
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if the shader compile failed, print the error message
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
	}
	//create a fragment shader object
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//attach the shader source code to the shader object and compile the shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check if the shader compile success
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if the shader compile failed, print the error message
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl;
	}

	shaderProgram = glCreateProgram();
	//attach the shader to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//link the program
	glLinkProgram(shaderProgram);
	//check if the program link success
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if the program link failed, print the error message
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}
	//delete the shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

//create a function to set up the vertex data
void hello_triangle::setVertexData() {
	//set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, //left
		0.5f, -0.5f, 0.0f, //right
		0.0f,  0.5f, 0.0f  //top
	};
	//create a vertex buffer object
	
	glGenBuffers(1, &VBO);
	//create a vertex array object	
	glGenVertexArrays(1, &VAO);
	//bind the vertex array object
	glBindVertexArray(VAO);
	//bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//copy the vertex data to the buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//enable the vertex attribute array
	glEnableVertexAttribArray(0);
	//unbind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the vertex array object
	glBindVertexArray(0);
}


//create a function to init OpenGL window
void hello_triangle::initOpenGL() {
	//load GLFW and create a window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	
	//check if the window create success
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	//make the window the current context
	glfwMakeContextCurrent(window);
	//initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//set the size of the rendering window
	glViewport(0, 0, 800, 600);
	//register the callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return;

}



