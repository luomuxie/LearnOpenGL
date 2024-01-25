#pragma once
// MouseInputUtility.h
#ifndef MOUSE_INPUT_UTILITY_H
#define MOUSE_INPUT_UTILITY_H

#include <GLFW/glfw3.h>
#include <camera.h>

class InputUtil {
public:
    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn, bool& firstMouse, float& lastX, float& lastY, Camera& camera);
    static void processInput(GLFWwindow* window, Camera& camera, float deltaTime);
};

#endif
