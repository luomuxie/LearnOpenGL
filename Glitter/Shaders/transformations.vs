#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 texCoord;
//create a transormtion input from C++ to vertex shader
uniform mat4 transform;

void main()
{
    gl_Position = vec4(aPos, 1.0)*transform;
    ourColor = aColor;
    texCoord = aTexCoord;
}