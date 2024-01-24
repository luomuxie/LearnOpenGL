#ifndef GRAPHICSWINDOWBASE_H
#define GRAPHICSWINDOWBASE_H

#include <GLFW/glfw3.h>
#include <camera.h>

class GraphicsWindowBase {
protected:
    GLFWwindow* window = nullptr;
    int scale = 1;
    int screen_width = 800*scale, screen_height = 600*scale; // Default screen size
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f)); // Default camera position
    //create a delta time
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float lastX = 400;
    float lastY = 300;
    bool firstMouse = true;

public:
    GraphicsWindowBase();
    virtual ~GraphicsWindowBase();

    void init_window();    
    void mouse_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);
    void input_process(GLFWwindow* window);

    virtual void run() = 0;
};

#endif // GRAPHICSWINDOWBASE_H
