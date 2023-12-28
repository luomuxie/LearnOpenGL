#version 330 core
layout (location = 0) in vec3 aPos;
//set the layout of the normal
layout (location = 1) in vec3 aNormal;
//set the layout of the texture
layout (location = 2) in vec2 aTexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 lightSpaceMatrix;

//create interface block
out VS_OUT {
	vec2 TexCoord;
	vec4 FragPos;	
	//add normal val
	vec3 Normal
	//add the fragPosInLightSpace with name like that
	vac4 FragPosLightSpace;
	
} vs_out;


void main()
{
	//get the martix of the normal to normalize it
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	//get the normal
	vs_out.Normal = normalMatrix * aNormal;

	//get the Fragpos 
	vs_out.FragPos = model * vec4(aPos, 1.0);	

	//get the texcoord
	vs_out.TexCoord = aTexCoord;

	//get the gl position
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	//get the fragPosInLightSpace
	vs_out.FragPosLightSpace = lightSpaceMatrix * vs_out.FragPos;
   
}