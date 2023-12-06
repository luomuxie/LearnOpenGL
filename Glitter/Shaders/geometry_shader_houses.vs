#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    //sign the gl_position
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}