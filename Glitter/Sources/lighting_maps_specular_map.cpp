#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "lighting_maps_specular_map.h"
#include <iostream>
#include <shader_s.h>
#include "func.h"
#include <glm/gtc/type_ptr.hpp>


void lighting_maps_specular_map::initOpenGL()
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
    Shader lightShader("..\\Glitter\\Shaders\\light.vs", "..\\Glitter\\Shaders\\light.fs");
    lightShader.use();
    lightShaderID = lightShader.ID;

    Shader cubeShader("..\\Glitter\\Shaders\\lighting_maps_diffuse.vs", "..\\Glitter\\Shaders\\lighting_maps_diffuse.fs");
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

void lighting_maps_specular_map::loadMap()
{
    //load diffuse map
    // load textures (we now use a utility function to keep the code more organized)
    diffuseMapID = loadTexture("..\\Glitter\\Img\\container2.png");
    //load specular map
    //specularMapID = loadTexture("..\\Glitter\\Img\\container2_specular.png");
}

void lighting_maps_specular_map::run()
{
    //init the openGL
    initOpenGL();
    //set the vertex data
    setVertexData();
    //init the shader
    initShader();
    //load the map
    loadMap();

    //set the render loop
    //judge if the window should close
    if (!glfwWindowShouldClose(window)) {
        //record the time of last frame
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //set the rendering commands here
        //set the background color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //clear the color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //process the input
        processInputColor(window);        

        //set the shader to use
        glUseProgram(lightShaderID);
        //set the model matrix
        glm::mat4 model = glm::mat4(1.0f);
        //scale the model matrix
        model = glm::scale(model, glm::vec3(0.2f));
        //translate the model matrix to lightPos
        model = glm::translate(model, lightPos);

        float radius = 5.0f;
        float angle = glfwGetTime();
        lightPos.x = radius * cos(angle);
        lightPos.z = radius * sin(angle);

        //set the model matrix uniform
        glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//set the view matrix
		glm::mat4 view = camera.GetViewMatrix();
		//set the projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 
			0.1f, 100.0f);
		//set the view matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//set the projection matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(lightShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));		
        //draw the light
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //set the cube shader to use
        glUseProgram(cubeShaderID);
        //set the model matrix uniform
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//set the view matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//set the projection matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		//set the viewPos uniform
		glUniform3f(glGetUniformLocation(cubeShaderID, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		//set the lightPos uniform
		glUniform3f(glGetUniformLocation(cubeShaderID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		//set the lightColor uniform
		glUniform3f(glGetUniformLocation(cubeShaderID, "lightColor"), 1.0f, 1.0f, 1.0f);
		//set the material uniform
		glUniform1i(glGetUniformLocation(cubeShaderID, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(cubeShaderID, "material.specular"), 1);
		glUniform1f(glGetUniformLocation(cubeShaderID, "material.shininess"), 32.0f);
		//set the diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMapID);
		//set the specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMapID);
		//draw the cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//draw the cube------------------------------------------------------
		//set the view matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//set the projection matrix uniform
		glUniformMatrix4fv(glGetUniformLocation(cubeShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		//set the viewPos uniform
		glUniform3f(glGetUniformLocation(cubeShaderID, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		
        //set the light's attributes
        //set the light's position
        glUniform3f(glGetUniformLocation(cubeShaderID, "light.position"), lightPos.x, lightPos.y, lightPos.z);
		//set the light's ambient
		glUniform3f(glGetUniformLocation(cubeShaderID, "light.ambient"), 0.2f, 0.2f, 0.2f);
        //set the light's diffuse
        glUniform3f(glGetUniformLocation(cubeShaderID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		//set the light's specular
		glUniform3f(glGetUniformLocation(cubeShaderID, "light.specular"), 1.0f, 1.0f, 1.0f);

        //set the material's attributes
        //set the material's shininess
        glUniform1f(glGetUniformLocation(cubeShaderID, "material.shininess"), 32.0f);
        //set the material's specular
        glUniform3f(glGetUniformLocation(cubeShaderID, "material.specular"), 0.5f, 0.5f, 0.5f);


		
		//set the diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMapID);
		//set the specular map
/*		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMapID); */       
		//draw the cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

        //----------------------------------------------------------------
        //enable the depth test
        glEnable(GL_DEPTH_TEST);                
		

		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
					
    }
    //delete the vbo and vao
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);

    //delete the window
    glfwDestroyWindow(window);
}

