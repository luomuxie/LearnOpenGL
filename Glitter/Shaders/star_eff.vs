//set version to 330
#version 330 core
layout (location = 0) in vec3 aPos;

//create a main to set gl_position
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, 0, 1.0);
}



