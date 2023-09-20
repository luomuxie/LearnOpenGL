// func.h
#ifndef FUNC_H
#define FUNC_H

struct GLFWwindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path);

#endif // FUNC_H
