#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

//out vec2 texCoord;
//create a out struct to pass to fragment shader
out VS_OUT {
	vec2 TexCoord;
	vec3 Normal;
	vec3 FragPos;
} vs_out;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0);

	//pass the normal to the fragment shader and the normal should be inverse transpose of the model matrix
	vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;

	vs_out.FragPos = vec3(model * vec4(aPos, 1.0));


    vs_out.TexCoord = aTexCoord;
}