#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "lighting_maps_specular_map.h"
#include <iostream>
#include <shader_s.h>

void lighting_maps_specular_map::initOpenGL()
{
	//init openGL
	glfwInit();
	//set the version of openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL to use the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//open the resizable window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create the window 
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "lighting_maps_specular_map", NULL, NULL);
	//judge if the window create successfully
	if (window == NULL)
	{
		std::cout << "Failed to create the window" << std::endl;
		glfwTerminate();
	}
	//set the window to the main context
	glfwMakeContextCurrent(window);
	//set the viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);	
}

void lighting_maps_specular_map::setVertexData()
{
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    //create the vao, vbo
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    //bind the vao, vbo
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //put the vertices into the vbo
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //set the vertex attribute
    //set the position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //enable the position attribute
    glEnableVertexAttribArray(0);
    //set the normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //enable the normal attribute
    glEnableVertexAttribArray(1);
    //set the texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //enable the texture attribute
    glEnableVertexAttribArray(2);
    //unbind the vao, vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //create the lightvao
    glGenVertexArrays(1, &lightVAO);
    //bind the lightvao
    glBindVertexArray(lightVAO);
    //bind the vbo
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //set the vertex attribute
    //set the position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //enable the position attribute
    glEnableVertexAttribArray(0);
    //unbind the vao, vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

void lighting_maps_specular_map::initShader()
{
    //create a shader class
    Shader lightShader("lighting_maps_specular_map.vs", "lighting_maps_specular_map.fs");
    lightShader.use();
    lightShaderID = lightShader.ID;

    Shader cubeShader("lighting_maps_specular_map.vs", "lighting_maps_specular_map_cube.fs");    
    cubeShader.use();
    cubeShaderID = cubeShader.ID;   
}

void lighting_maps_specular_map::processInputColor(GLFWwindow* window)
{
    //judge if the esc is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
		//close the window
		glfwSetWindowShouldClose(window, true);
	}
    //judge if the w is pressed
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
		//move the camera forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
    //judge if the s is pressed
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
		//move the camera backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	//judge if the a is pressed
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
		//move the camera left
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	//judge if the d is pressed
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
		//move the camera right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void lighting_maps_specular_map::loadTexture()
{
    //load diffuse map
    //diffuseMap = loadTexture("container2.png");
}
