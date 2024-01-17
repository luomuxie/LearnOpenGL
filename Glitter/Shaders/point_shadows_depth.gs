#version 330 core
//set the geometry to triangles for the cube depth map
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

//get the matrices array  from application
uniform mat4 shadowMatrices[6];

//out variables for the fragment shader
out vec4 FragPos;

void main()
{
	//loop through the triangles
	for(int i = 0; i < 3; i++)
	{
		//get the position of the vertex
		FragPos = gl_in[i].gl_Position;
		//loop through the matrices
		for(int j = 0; j < 6; j++)
		{
			//set the gl_Position to the transformed vertex
			gl_Position = shadowMatrices[j] * FragPos;
			//emit the vertex
			EmitVertex();
		}
		//end the primitive
		EndPrimitive();
	}
}