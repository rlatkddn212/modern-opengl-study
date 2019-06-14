#version 430 core
out vec4 color;

in VERTEX_OUT
{
	vec4 color;
}frg_in;

void main()
{
	color = frg_in.color;
}