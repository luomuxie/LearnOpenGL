// func.h
#include <iostream>
#include <vector>
#ifndef FUNC_H
#define FUNC_H

struct GLFWwindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path);
//create a func to loadCubeTexture
unsigned int loadCubeTexture(std::vector<std::string> faces);

#endif // FUNC_H
