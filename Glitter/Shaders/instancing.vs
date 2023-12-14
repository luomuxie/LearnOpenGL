#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aOffset;

out vec3 fColor;

//create a mian func 
void main()
{
	//set the color
	fColor = aColor;	
	gl_Position = vec4(aPos + aOffset, 0, 1.0);

}

