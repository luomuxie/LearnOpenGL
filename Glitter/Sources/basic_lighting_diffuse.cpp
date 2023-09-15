#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "basic_lighting_diffuse.h"
#include <iostream>
#include "func.h"
#include <shader_s.h>
#include <camera.h>
#include <glm/gtc/type_ptr.hpp>

void basic_lighting_diffuse::initOpenGL()
{
	//init glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set the openGL to use the core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the window not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	//if the window is null,then print the error
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	//set the current context
	glfwMakeContextCurrent(window);
	//set the callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//init the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//set the view port
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void basic_lighting_diffuse::setVertexData()
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
    //create a vertex buffer object
    glGenBuffers(1, &VBO);

    //create a vertex array object
    glGenVertexArrays(1, &cubeVAO);
    //bind the vertex array object
    glBindVertexArray(cubeVAO);
    //bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //copy the vertices data into the vertex buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //set the vertex attribute pointers
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    //create the light cube
    glGenVertexArrays(1, &lightVAO);
    //bind the vertex array object
    glBindVertexArray(lightVAO);
    //bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //set the vertex attribute pointers
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    //unbind the vertex array object
    glBindVertexArray(0);
    //unbind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, 0);   

}

void basic_lighting_diffuse::initShader()
{
    //create the shader program
    Shader lightingShader("..\\Glitter\\Shaders\\light.vs", "..\\Glitter\\Shaders\\light.fs");
    lightingShader.use();
    lightShaderID = lightingShader.ID;

    //create the cubeshader
    Shader cubeShader("..\\Glitter\\Shaders\\colors_2.vs", "..\\Glitter\\Shaders\\colors_2.fs");
    cubeShader.use();
    cubeShaderID = cubeShader.ID;    
}

void basic_lighting_diffuse::processInputColor(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void basic_lighting_diffuse::run()
{
    //init the openGL
    initOpenGL();
    //set the vertex data
    setVertexData();
    //init the shader
    initShader();

    //set the render loop
    while (!glfwWindowShouldClose(window)) {
		//set the frame time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//process the input
		processInputColor(window);

		//set the background color
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //create light cube data
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        //create view matrix
        glm::mat4 view = camera.GetViewMatrix();
        //create projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.f);
        //use the light shader
        glUseProgram(lightShaderID);
        //set the model matrix
        glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //set the view matrix
        glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        //set the projection matrix
        glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //bind the vertex array object
        glBindVertexArray(lightVAO);
        //draw the light cube
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //create cube data
        model = glm::mat4(1.0f);        
        //use the cube shader
        glUseProgram(cubeShaderID);
        //set the model matrix
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //set the view matrix
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        //set the projection matrix
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //set light color
        glUniform3f(glGetUniformLocation(cubeShaderID, "lightColor"), 1.0f, 1.0f, 1.0f);
        //set object color
        glUniform3f(glGetUniformLocation(cubeShaderID, "objectColor"), 1.0f, 0.5f, 0.31f);    
        //set light position
        glUniform3f(glGetUniformLocation(cubeShaderID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

        //bing the vertex array object
        glBindVertexArray(cubeVAO);
        //draw the cube
        glDrawArrays(GL_TRIANGLES, 0, 36);
		
        //open the depth test
        glEnable(GL_DEPTH_TEST);

        //swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
    }

    //delete the VAO
    glDeleteVertexArrays(1, &cubeVAO);
    //delete the VAO
    glDeleteVertexArrays(1, &lightVAO);
    //delete the VBO
    glDeleteBuffers(1, &VBO);

    //delete the window
    glfwTerminate();




}
