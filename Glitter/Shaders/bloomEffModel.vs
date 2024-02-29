#version 330 core
// in apos
layout(location = 0) in vec3 aPos;
// in anormal
layout(location = 1) in vec3 aNormal;
// in atexcoord
layout(location = 2) in vec2 aTexCoord;

//uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//out uv
out vec2 Texcoords;




void main()
{	
	gl_Position = projection*view*model*vec4(aPos, 1.0);
	Texcoords = aTexCoord;
}
