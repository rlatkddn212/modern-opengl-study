#version 420 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vs_color;

void main(void)
{
	gl_Position = vec4(position.xyz, 1.0); 
	vs_color = color;
}
