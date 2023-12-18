#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;


//create interface block for the vertex shader
in VS_OUT {
    vec2 texCoords;
} gs_in[];


out vec2 TexCoords; 

//create a uniform for the time
uniform float time;

//calculate the normal of a triangle
vec3 calc_normal(vec3 v0, vec3 v1, vec3 v2)
{
	vec3 edge1 = v0 - v1;
	vec3 edge2 = v2 - v1;
	return normalize(cross(edge1, edge2));
}

//create a func to move the position of the vertex by normal and time with sin func
vec3 move_vertex(vec3 vertex, vec3 normal)
{
	//create a dis
	float dis = 2.0f;
	//calculate the dis by sin func and in 0 to 1
	vec3 dir = normal *((sin(time) + 1.0f) / 2.0f)*dis;
	//move the vertex
	return vertex + dir;
}


//create a main function for the geometry shader
void main()
{
	//get the normal of the triangle
	vec3 normal = calc_normal(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz);

    //create a loop for the triangles
	for (int i = 0; i < 3; i++){
		//move the vertex
		vec3 pos = move_vertex(gl_in[i].gl_Position.xyz, normal);
		//set the position
		gl_Position = vec4(pos, 1.0f);
		//set the texcoord 
		TexCoords = gs_in[i].texCoords;
		//emit the vertex
		EmitVertex();
	}

	EndPrimitive();
}