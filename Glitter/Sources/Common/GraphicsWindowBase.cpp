// GraphicsWindowBase.cpp
#include "GraphicsWindowBase.h"
#include <glad/glad.h>
#include <iostream>
#include "../InputUtil.h"

GraphicsWindowBase::GraphicsWindowBase() {
    
}

GraphicsWindowBase::~GraphicsWindowBase() {
    glfwTerminate();
}

void GraphicsWindowBase::init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(screen_width, screen_height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        GraphicsWindowBase* instance = static_cast<GraphicsWindowBase*>(glfwGetWindowUserPointer(window));
        instance->mouse_callback(xpos, ypos);
        });

    //set the callback function for the scroll
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        GraphicsWindowBase* instance = static_cast<GraphicsWindowBase*>(glfwGetWindowUserPointer(window));
        instance->scroll_callback(xoffset, yoffset);
        });


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
    }

    glViewport(0, 0, screen_width, screen_height);
}

void GraphicsWindowBase::run() {
    init_window();
    while (!glfwWindowShouldClose(window)) {        
        float currentFrame = glfwGetTime();        
        deltaTime = currentFrame - lastFrame;        
        lastFrame = currentFrame;

        input_process(window);        

        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
}

void GraphicsWindowBase::scroll_callback(double xoffset, double yoffset)
{
    //process the scroll
    camera.ProcessMouseScroll(yoffset);
}


void GraphicsWindowBase::mouse_callback(double xpos, double ypos)
{
    InputUtility::mouseCallback(window, xpos, ypos, firstMouse, lastX, lastX, camera);
}

void GraphicsWindowBase::input_process(GLFWwindow* window) {
	InputUtility::processInput(window, camera,deltaTime);
}
