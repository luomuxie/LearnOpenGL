#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


uniform mat4 model;
uniform mat4 lightSpaceMatrix;

//create a val to out texture coordinates to the fragment shader
out vec2 TexCoord;




void main()
{
    gl_Position = lightSpaceMatrix*view*model*vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}