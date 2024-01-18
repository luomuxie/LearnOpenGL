#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//a bool val for reverse the normal
uniform bool reverse_normals;

//a out struct for fragment shader
out VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} vs_out;



void main()
{
    
    //reverse the normal if needed
    vec3 normal = aNormal;
    if(reverse_normals){
        normal = -normal;
    }

    //cal the normal matrix to reverse the normal
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vs_out.Normal = normalize(normalMatrix*normal);

    //cal the position of the vertex
    vec4 pos = vec4(aPos, 1.0);
    vs_out.FragPos = vec3(model*pos);

    gl_Position = projection * view * model * vec4(aPos, 1.0);

    vs_out.TexCoords = aTexCoord;

}