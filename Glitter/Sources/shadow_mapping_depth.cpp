#include "shadow_mapping_depth.h"
#include <glad/glad.h>
#include <iostream>
#include <shader_s.h>
#include "func.h"

void shadow_mapping_depth::initOpenGL()
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
	//glfwWindowHint(GLFW_SAMPLES, 4);
	

	//create a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "shadow_mapping_depth", nullptr, nullptr);

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
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void shadow_mapping_depth::initVertex()
{
	float planeVertices[] = {
		// positions            // normals         // texcoords
		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};
    float cubeVertices[] = {
        // back face
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
        // front face
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
         1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
        // left face
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
        -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
        // right face
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
         1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
         1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
         // bottom face
         -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
          1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
          1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
          1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
         -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
         -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
         // top face
         -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
          1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
          1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
          1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
         -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
         -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
    };

    //set plane data
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);

    //bind plane vao and vbo
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    //set plane vbo data
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    //enable the plane pointer
    glEnableVertexAttribArray(0);
    //set the plane pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //enable the plane normal pointer
    glEnableVertexAttribArray(1);
    //set the plane normal pointer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //enable the plane uv pointer
    glEnableVertexAttribArray(1);
    //set the plane uv pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    glBindVertexArray(0);

    //set cube data----------------------------------------------------------------
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    //bind cube vao and vbo
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    //set cube vbo data
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    //enable the cube pointer
    glEnableVertexAttribArray(0);
    //set the cube pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //enable the cube normal pointer
    glEnableVertexAttribArray(1);
    //set the cube normal pointer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //enable the cube uv pointer
    glEnableVertexAttribArray(1);
    //set the cube uv pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //unbind the vao
    glBindVertexArray(0);
     
}



void shadow_mapping_depth::initFramebuffer()
{
    //create depth map FBO
    glGenBuffers(1, &depthMapFBO);

    //create depth map texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    //set the depth map texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT,
        		0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    //set the depth map texture parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //set the depth map texture parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //set the depth map texture parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //set the depth map texture parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);


    //bind the depth map FBO
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    //attach the depth map texture to the depth map FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    //set the draw buffer
    glDrawBuffer(GL_NONE);
    //set the read buffer
    glReadBuffer(GL_NONE);
    //unbind the depth map FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void shadow_mapping_depth::run()
{
    initOpenGL();
    initVertex();
    //create shader by shader class 
    Shader shader("shadow_mapping_depth.vs", "shadow_mapping_depth.fs");
    Shader simpleDepthShader("shadow_mapping_depth_depth.vs", "shadow_mapping_depth_depth.fs");
    
    //create main loop
    while (!glfwWindowShouldClose(window))
    {
		//set the input
		processInput(window);

		//set the background color
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set the viewport
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

        //render depth of scene to texture (from light's perspective)
        // --------------------------------------------------------------
        //bind the depth map FBO
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        //set the viewport
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        
        //use the simple depth shader
        simpleDepthShader.use();
        //create a light space matrix
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        //set the light projection
        float near_plane = 1.0f, far_plane = 7.5f;

        //set the light projection
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f,
            				near_plane, far_plane);
        //set the light view
        lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
            							glm::vec3(0.0f, 0.0f, 0.0f),
            							glm::vec3(0.0f, 1.0f, 0.0f));

        //set the light space matrix
        lightSpaceMatrix = lightProjection * lightView;
        //set the value of the uniform
        simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
        
        //draw the plane
        glBindVertexArray(planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //draw the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //unbind the framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //reset the viewport
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


        //render the scene
        glm::mat4 model = glm::mat4(1.0f);
		//swap the buff
        glfwSwapBuffers(window);
        //poll the event
        glfwPollEvents();
    }

    //end the program
    glfwTerminate();

}
