#version 330 core
// in apos
layout(location = 0) in vec3 aPos;
// in anormal
layout(location = 1) in vec3 aNormal;
// in atexcoord
layout(location = 2) in vec2 aTexCoord;

//create a out struct to pass the data to the fragment shader
out VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} vs_out;


//uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{	
	gl_Position = projection*view*model*vec4(aPos, 1.0);

	//inverse the normal matrix
	mat3 normalMatrix = transpose(inverse(mat3(model)));

	//pass the data to the fragment shader
	vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
	vs_out.Normal = normalMatrix * aNormal;
	vs_out.TexCoords = aTexCoord;
}
