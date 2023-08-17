#include "hello_rect.h"
#include "shaders_uniform.h"
#include "shaders_interpolation.h"
#include "shaders_class.h"
#include <iostream>
#include <windows.h>

int main(int argc, char* argv[]) {
        
/*    hello_triangle hw;
    hw.hello_triangleOpenGL(); */   

    //hello_rect hr;
    //hr.hello_rectOpenGL();

    //shaders_uniform su;
    //su.shaders_uniformOpenGL();

    //shaders_interpolation si;
    //si.run();

    char buffer[MAX_PATH];
    if (GetCurrentDirectory(MAX_PATH, buffer)) {
        std::cout << "Current working directory: " << buffer << std::endl;
    }
    else {
        std::cerr << "Error getting current directory" << std::endl;
    }

    shaderClass sc;
    sc.run();

}


