#version 330 core
layout (points) in;
//create triangle stream for the geometry shader to output to
layout (triangle_strip, max_vertices = 5) out;


//cretae func to build a house
void buildHouse(vec4 position)
{
	//create five vertices for the house
	gl_Position = position + vec4(-0.2,-0.2, 0.0, 0.0);
	EmitVertex();
	gl_Position = position + vec4(0.2,-0.2, 0.0, 0.0);
	EmitVertex();
	gl_Position = position + vec4(-0.2,0.2, 0.0, 0.0);
	EmitVertex();
	gl_Position = position + vec4(0.2,0.2, 0.0, 0.0);
	EmitVertex();
	gl_Position = position + vec4(0.0,0.4, 0.0, 0.0);
	EmitVertex();
	EndPrimitive();

}
//create a main function for the geometry shader
void main()
{
	//use the build house function to build a house for each vertex
	buildHouse(gl_in[0].gl_Position);
}