#version 430 core

uniform sampler2D image;
in VERTEX_OUT
{
	vec2 vt;
}frg_in;

out vec4 color;

void main()
{
	color = texture(image, frg_in.vt);
}