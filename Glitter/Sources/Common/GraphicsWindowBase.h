#ifndef GRAPHICSWINDOWBASE_H
#define GRAPHICSWINDOWBASE_H

#include <GLFW/glfw3.h>
#include <camera.h>
#include <iostream>
#include <shader_s.h>

class GraphicsWindowBase {
protected:
    GLFWwindow* window = nullptr;
    int scale = 1;
    int screenWidth = 800*scale, screenHeight = 600*scale; // Default screen size
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f)); // Default camera position
    //create a delta time
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float lastX = 400;
    float lastY = 300;
    bool firstMouse = true;

    Shader CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const std::string& geometryShaderSource = "");
    Shader CreateEffShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const std::string& geometryShaderSource = "");
    //create a func to get the camera's projection matrix and set the default zNear and zFar
    glm::mat4 GetProjectionMatrix(float zNear = 0.1f, float zFar = 100.0f);

    //create a func to get the camera's view matrix
    glm::mat4 GetViewMatrix();
     //create a fun to loadTexture
    unsigned int LoadTexture(const std::string& texture);
    void InitWindow();
    void MouseCallback(double xpos, double ypos);
    void ScrollCallback(double xoffset, double yoffset);
    virtual void InputProcess(GLFWwindow* window);

    //creat a func to render cube
    //create cubevao and vbo
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    void RenderCube();
    //create a func to render plane
    //create planevao and vbo
	unsigned int quadVAO = 0;
	unsigned int quadVBO = 0;
	void RenderQuad();

       
public:
    GraphicsWindowBase();
    virtual ~GraphicsWindowBase();
    virtual void Run() = 0;
};

#endif // GRAPHICSWINDOWBASE_H
