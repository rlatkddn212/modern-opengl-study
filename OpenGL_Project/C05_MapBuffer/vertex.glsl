#version 420 core

layout (location = 0) in vec4 position;

void main(void)
{
	gl_Position = vec4(position.xyz, 1.0); 
}
