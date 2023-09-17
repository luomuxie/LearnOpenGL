#include <glad/glad.h>
#include "materials.h"
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <glm/gtc/type_ptr.hpp>

void materials::initOpenGL()
{
	//init the glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL to use the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create4 a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	//if the window is null,then print the error
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}
	//set the window to the current context
	glfwMakeContextCurrent(window);
	//set the callback func if the window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		//return -1;
	}
	//set the openGL viewport position and size
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void materials::setVertexData()
{
    //create a cube vertex data array and the normal vector array
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    //create a vertex buffer object and copy the vertex data to it
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //create the cubeVAO array object    
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    //set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //set the normal attribute pointers
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //create the lightVAO array object
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    //set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //unbind the VAO
    glBindVertexArray(0);
    //unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
   
}

void materials::initShader()
{
	////create the shader program
	//Shader shader = new Shader("shaders/materials.vs", "shaders/materials.fs");
	//lightShader = new Shader("shaders/light.vs", "shaders/light.fs");

    Shader cubeShader("..\\Glitter\\Shaders\\materials.vs", "..\\Glitter\\Shaders\\materials.fs");
    Shader lightShader("..\\Glitter\\Shaders\\light.vs", "..\\Glitter\\Shaders\\light.fs");
    
    cubeShader.use();
    lightShader.use();

    //set ID
    cubeShaderID = cubeShader.ID;
    lightShaderID = lightShader.ID;    
}

void materials::processInputColor(GLFWwindow* window)
{
    //if the escape key is pressed, then close the window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

    //if the w key is pressed, then move the camera forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
    //if the s key is pressed, then move the camera backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
	//if the a key is pressed, then move the camera left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
    //if the d key is pressed, then move the camera right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void materials::run()
{
    //init the opengl
    initOpenGL();
    //init the shader
    initShader();
    //init the vertex data
    setVertexData();

    //render loop
    while (!glfwWindowShouldClose(window))
    {
		//calculate the delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//process the input
		processInputColor(window);

		//clear the color buffer and depth buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		//set the view matrix
		glm::mat4 view = camera.GetViewMatrix();
		//set the projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
		

        //create a model matrix
        glm::mat4 model = glm::mat4(1.0f);
        //set the model position to the lightPos
        model = glm::translate(model, lightPos);
        //set the model scale
        model = glm::scale(model, glm::vec3(0.2f));
        //set the model matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //set the view matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        //set the projection matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //use the light shader
        glUseProgram(lightShaderID);        
        //draw the light
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //use the cube shader
        glUseProgram(cubeShaderID);
        //create a model matrix
        model = glm::mat4(1.0f);
        //set the model matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //set the view matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        //set the projection matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //set the view position to the shader
        glUniform3fv(glGetUniformLocation(cubeShaderID, "viewPos"), 1, glm::value_ptr(camera.Position));
        //set the light position to the shader
        glUniform3fv(glGetUniformLocation(cubeShaderID, "lightPos"), 1, glm::value_ptr(lightPos));
        //set light color
        glUniform3f(glGetUniformLocation(cubeShaderID, "lightColor"), 1.0f, 1.0f, 1.0f);
        //set object color
        glUniform3f(glGetUniformLocation(cubeShaderID, "objectColor"), 1.0f, 0.5f, 0.31f);
        
        //darw the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //open the depth test
        glEnable(GL_DEPTH_TEST);

        //swap the buffer
        glfwSwapBuffers(window);
        //poll the event
        glfwPollEvents();
    }

    //delete the vbo and vao
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);   

    //delete the window 
    glfwDestroyWindow(window);
}


