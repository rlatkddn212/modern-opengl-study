#version 430 core
out vec4 color;
in vec4 vs_color;

void main()
{
		color = vs_color;
}