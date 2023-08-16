#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders_interpolation.h"
#include <iostream>
#include "func.h"

void shaders_interpolation::initOpenGL()
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

void shaders_interpolation::setVertexData()
{
	//create the vertex data and the data of the color
	float vertices[] = {
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};


	//create the indices
	//unsigned int indices[] = {
	//	0, 1, 2, //first triangle
	//	1, 2, 3 //second triangle
	//};

	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//bind the VAO
	glBindVertexArray(VAO);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the data of the VBO
	//bind the EBO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	
	//set the data of the EBO
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//enable the vertex attribute
	//glEnableVertexAttribArray(0);
	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the VAO
	glBindVertexArray(0);
	//unbind the EBO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void shaders_interpolation::initShaderProgram()
{
	//create the vertex shader source
	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n" //the position variable has attribute position 0
		// the color variable has attribute position 1
		"layout(location = 1) in vec3 aColor;\n" //the color variable has attribute position 1		

		"out vec3 vertexColor;\n" //specify a color output to the fragment shader
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos, 1.0);\n" //see how we directly give a vec3 to vec4's constructor
		"vertexColor = aColor;" //set the output variable to a dark-red color
		"}\0";

	//create the fragment shader source
	const char* fragmentShaderSource = "#version 330 core\n"
		//"uniform vec4 ourColor;\n"
		"out vec4 FragColor;\n"
		"in vec3 vertexColor;\n" //the input variable from the vertex shader (same name and same type)
		"void main()\n"
		"{\n"
		"FragColor = vec4(vertexColor,1) ;\n" //set the output variable to a dark-red color
		"}\0";

	//create the vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//compile the vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check the vertex shader
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if the vertex shader is not compiled,then print the error
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//create the fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//compile the fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check the fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if the fragment shader is not compiled,then print the error
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Link the vertex and fragment shader into a shader program
	
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// After linking, we no longer need these shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


}


void shaders_interpolation::run()
{
	//initiate the openGL
	initOpenGL();
	//set the vertex data
	setVertexData();
	//initiate the shader program
	initShaderProgram();

	//render loop
	while (!glfwWindowShouldClose(window)) {
		//process the input
		processInput(window);

		//render
		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//draw the triangle
		//use the shader program
		glUseProgram(shaderProgram);
		//set the uniform
		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//float redVal = cos(timeValue) / 2.0f + 0.5f;

		////get the uniform location
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		////set the uniform
		//glUniform4f(vertexColorLocation, redVal, greenValue, redVal, 1.0f);

		//bind the VAO
		glBindVertexArray(VAO);
		//draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);		
		//unbind the VAO
		glBindVertexArray(0);

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
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
}