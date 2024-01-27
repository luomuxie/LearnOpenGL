#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;
layout (location = 1) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;


//create interface block
out VS_OUT {	
	vec3 FragPos;		
	vec2 TexCoords;

	//add tangentLightPos
	vec3 TangentLightPos;
	//add tangentViewPos
	vec3 TangentViewPos;
	//add tangent fragPos
	vec3 TangentFragPos;

} vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//add lightPos
uniform vec3 lightPos;
//add viewPos
uniform vec3 viewPos;



void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0);
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
	vs_out.TexCoords = aTexCoord;

	//retrieve normal matrix
	mat3 normalMatrix = transpose(inverse(mat3(model)));

	//calculate tangent and bitangent
	vec3 T = normalize(normalMatrix * aTangent);
	vec3 N = normalize(normalMatrix * aNormal);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	//calculate TBN
	mat3 TBN = transpose(mat3(T, B, N));
	vs_out.TangentLightPos = TBN * lightPos;
	vs_out.TangentViewPos = TBN * viewPos;
	vs_out.TangentFragPos = TBN * vs_out.FragPos;
}