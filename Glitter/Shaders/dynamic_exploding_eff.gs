#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

//creaet a interface block for the vertex shader
in VS_OUT
{
	vec2 texCoords;
} gs_in[];

//create a out vec3  for the fragment shader
out vec2 TexCoords;


//create a uniform for the time
uniform float time;

//calculate the normal of a triangle
vec3 normal(vec3 v0, vec3 v1, vec3 v2)
{
	vec3 a = v0 - v1;
	vec3 b = v2 - v1;
	return normalize(cross(a, b));
}

//calculate the position of a vertex
vec3 move_vertex(vec3 vertex, vec3 normal)
{
	//create a dis
	float dis = 2.0f;
	//calculate the dis by sin func and in 0 to 1
	vec3 dir = normal *((sin(time) + 1.0f) / 2.0f)*dis;
	//move the vertex
	return vertex + dir;
}

void main()
{
	//get the normal of the triangle
	vec3 n = normal(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz);

	for(int i = 0; i < gl_in.length(); i++)
	{
		//move the vertex
		vec3 pos = move_vertex(gl_in[i].gl_Position.xyz, n);
		//set the position
		gl_Position = vec4(pos, 1.0f);
		//emit the vertex
		TexCoords = gs_in[i].texCoords;

		EmitVertex();
	}

	//end the primitive
	EndPrimitive();
}

