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
    for(int face = 0; face < 6; ++face)
    {
        gl_Layer = face; // built-in variable that specifies to which face we render.
        for(int i = 0; i < 3; ++i) // for each triangle's vertices
        {
            FragPos = gl_in[i].gl_Position;
            gl_Position = shadowMatrices[face] * FragPos;
            EmitVertex();
        }    
        EndPrimitive();
	}
}