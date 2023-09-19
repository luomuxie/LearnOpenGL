#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "lighting_maps_diffuse.h"
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <camera.h>
#include <glm/gtc/type_ptr.hpp>


void lighting_maps_diffuse::initOpenGL()
{
	 //init the openGL
	//init the glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL to the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window not to be resizable
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "lighting_maps_diffuse", NULL, NULL);
	//judge if the window is created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create the window" << std::endl;
		glfwTerminate();
	}
	//set the window to the main context
	glfwMakeContextCurrent(window);
	//set the window to change the size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init the GLAD" << std::endl;
		glfwTerminate();
	}

	//set the viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);	
}


void lighting_maps_diffuse::setVertexData()
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

    //bind the vao
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    //bind the vbo
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //set the vbo data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //set the vertex attribute
    //set the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //enable the vertex position
    glEnableVertexAttribArray(0);
    //set the vertex normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //enable the vertex normal
    glEnableVertexAttribArray(1);
    //set the vertex texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //enable the vertex texture
    glEnableVertexAttribArray(2);

    //set the light vao
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    //set the vertex attribute
    //set the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //enable the vertex position
    glEnableVertexAttribArray(0);
    
    //unbind the vao
    glBindVertexArray(0);
    //unbind the vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void lighting_maps_diffuse::initShader()
{
    //create a shader class 
    Shader lightShader("lighting_maps_diffuse.vs", "lighting_maps_diffuse.fs");
    lightShaderID = lightShader.ID;

    Shader cubeShader("lighting_maps_diffuse.vs", "lighting_maps_diffuse_cube.fs");
    cubeShaderID = cubeShader.ID;        
}

void lighting_maps_diffuse::processInputColor(GLFWwindow* window)
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
		//set the camera position
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
    //judge if the s is pressed
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        //set the camera position
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    //judge if the a is pressed
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
		//set the camera position
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
    //judge if the d is pressed
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
		//set the camera position
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}



}

void lighting_maps_diffuse::run()
{
    //init the openGL
    initOpenGL();
    //set the vertex data
    setVertexData();
    //init the shader
    initShader();
    
    //render loop
    //judge if the window is closed
    while (!glfwWindowShouldClose(window))
    {
        //set the time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //process the input
        processInputColor(window);
        //set the background color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //clear the color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw the the lightcube
        //use the lightshader
        glUseProgram(lightShaderID);
        //bind the vao
        glBindVertexArray(lightVAO);

        //set the view matrix
        glm::mat4 view = camera.GetViewMatrix();
        //set the projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        //create a model matrix
        glm::mat4 model = glm::mat4(1.0f);
        //set the model position to the lightPos
        model = glm::translate(model, lightPos);




        //open the z buffer
        glEnable(GL_DEPTH_TEST);
        

    }



    



   

}
