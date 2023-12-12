#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


uniform mat4 model;
uniform mat4 view;

out VS_OUT {
	vec3 normal;
} vs_out;


void main()
{    
    gl_Position = view * model * vec4(aPos, 1.0);
	//vs_out.normal = aNormal;
    //calculate the normal matrix
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	//transform the normal's orientation
	vs_out.normal = normalize(normalMatrix * aNormal);
}