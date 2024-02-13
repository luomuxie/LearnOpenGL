// GraphicsWindowBase.cpp
#include "GraphicsWindowBase.h"
#include <glad/glad.h>
#include <iostream>
#include "InputUtil.h"
#include <shader_s.h>
#include "Constants.h"
#include "../func.h"

GraphicsWindowBase::GraphicsWindowBase() {
    screenWidth = 800;
	screenHeight = 600;
	lastX = screenWidth / 2.0f;
	lastY = screenHeight / 2.0f;
	firstMouse = true;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    cubeVAO = 0;
    cubeVBO = 0;
}

GraphicsWindowBase::~GraphicsWindowBase() {
    glfwTerminate();
}

void GraphicsWindowBase::InitWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        GraphicsWindowBase* instance = static_cast<GraphicsWindowBase*>(glfwGetWindowUserPointer(window));
        instance->MouseCallback(xpos, ypos);
        });

    //set the callback function for the scroll
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        GraphicsWindowBase* instance = static_cast<GraphicsWindowBase*>(glfwGetWindowUserPointer(window));
        instance->ScrollCallback(xoffset, yoffset);
        });


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
    }

    glViewport(0, 0, screenWidth, screenHeight);
}

void GraphicsWindowBase::Run() {
    InitWindow();
    while (!glfwWindowShouldClose(window)) {        
        float currentFrame = glfwGetTime();        
        deltaTime = currentFrame - lastFrame;        
        lastFrame = currentFrame;

        InputProcess(window);        

        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
}

void GraphicsWindowBase::ScrollCallback(double xoffset, double yoffset)
{
    //process the scroll
    camera.ProcessMouseScroll(yoffset);
}


void GraphicsWindowBase::MouseCallback(double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        InputUtil::mouseCallback(window, xpos, ypos, firstMouse, lastX, lastX, camera);
    }
    else {
        firstMouse = true;
    }
}

void GraphicsWindowBase::InputProcess(GLFWwindow* window) {
	InputUtil::processInput(window, camera,deltaTime);
}

void GraphicsWindowBase::RenderCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        float vertices[] = {
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
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void GraphicsWindowBase::RenderQuad()
{

    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

Shader GraphicsWindowBase::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource,const std::string& geometryShaderSource) {
    //create a vertexShaderPath str
    std::string vertexPath = SHADER_PATH + vertexShaderSource+".vs";
    std::string fragmentPath = SHADER_PATH + fragmentShaderSource +".fs";
    //check if geometryShaderSource is empty
    std::string geometryPath = "";    
    if (!geometryShaderSource.empty()) {
		geometryPath = SHADER_PATH + geometryShaderSource + ".gs";
        Shader shader(vertexPath.c_str(), fragmentPath.c_str(), geometryPath.c_str());
        return shader;
	}
    Shader shader(vertexPath.c_str(), fragmentPath.c_str());
    return shader;        
}

Shader GraphicsWindowBase::CreateEffShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const std::string& geometryShaderSource) {
    //create a vertexShaderPath str
    std::string vertexPath = SHADER_Eff_PATH + vertexShaderSource + ".vs";
    std::string fragmentPath = SHADER_Eff_PATH + fragmentShaderSource + ".fs";
    //check if geometryShaderSource is empty
    std::string geometryPath = "";
    if (!geometryShaderSource.empty()) {
        geometryPath = SHADER_Eff_PATH + geometryShaderSource + ".gs";
        Shader shader(vertexPath.c_str(), fragmentPath.c_str(), geometryPath.c_str());
        return shader;
    }
    Shader shader(vertexPath.c_str(), fragmentPath.c_str());
    return shader;
}

glm::mat4 GraphicsWindowBase::GetProjectionMatrix(float zNear, float zFar)
{
    return glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, zNear, zFar);
}

glm::mat4 GraphicsWindowBase::GetViewMatrix()
{
    return camera.GetViewMatrix();
}

unsigned int GraphicsWindowBase::LoadTexture(const std::string& texture)
{
    return loadTexture((TEXTURE_PATH + texture).c_str());;
}
