#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//create a mat for lightSpaceMatrix
uniform mat4 lightSpaceMatrix;

void main()
{
	//gl_Position = projection * view * model * vec4(aPos, 1.0);
	gl_Position =  lightSpaceMatrix * model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}

