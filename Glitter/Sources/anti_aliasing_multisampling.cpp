#include "anti_aliasing_multisampling.h"
#include <glad/glad.h>
#include <iostream>
#include <shader_s.h>
#include "Constants.h"



void anti_aliasing_multisampling::initOpengl()
{
	//init glfw
	glfwInit();
	//set opengl version 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set opengl profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window can be resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	//open opengl samper for 4
	glfwWindowHint(GLFW_SAMPLES, 4);
	

	//create a window
	window = glfwCreateWindow(width, height, "anti_aliasing_multisampling", nullptr, nullptr);

	//check the window is created or not
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	//set the window to the current context
	glfwMakeContextCurrent(window);

	//init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
	}

	//set the size of the viewport
	glViewport(0, 0, width, height);
}

void anti_aliasing_multisampling::setVertexData()
{
    GLfloat cubeVertices[] = {
        // Positions       
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
        -0.5f,  0.5f, -0.5f
    };

    //set the vao and vbo
    glGenVertexArrays(1, &cubeVao);
    glGenBuffers(1, &cubeVbo);

    //bind the vao and vbo
    glBindVertexArray(cubeVao);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);

    //set the vbo data
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    //set the attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    //enable the vertex attribute array
    glEnableVertexAttribArray(0);
    //unbind the vao and vbo
    glBindVertexArray(0);    
}

void anti_aliasing_multisampling::run()
{
	//init opengl 
	initOpengl();

	//set the vertex data
	setVertexData();

	//create the shader
	Shader shader((SHADER_PATH + "anti_aliasing_multisampling.vs").c_str(), (SHADER_PATH + "anti_aliasing_multisampling.fs").c_str());

	//create the projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

	//open the depth test
	glEnable(GL_DEPTH_TEST);

	//open anti_aliasing_multisampling
	glEnable(GL_MULTISAMPLE);

	//create the main loop
    while (!glfwWindowShouldClose(window))
    {
		

		//set the color of the screen
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		//clear the color buffer and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use the shader
		shader.use();
		//create a view;
		glm::mat4 view = camera.GetViewMatrix();		

		//create a modle;
		glm::mat4 model = glm::mat4(1.0f);

		//rotate the model 45angle
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		
		//set the value of the uniform
		shader.setMat4(shader.VIEW, view);
		shader.setMat4(shader.PROJECTION, projection);
		shader.setMat4(shader.MODEL,model);

		//draw the cube
		glBindVertexArray(cubeVao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	//delete the vertex array object
	glDeleteVertexArrays(1, &cubeVao);
	//delete the vertex buffer object
	glDeleteBuffers(1, &cubeVbo);
	//terminate glfw
	glfwTerminate();
}
