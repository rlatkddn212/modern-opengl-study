#version 420 core

layout (location = 0) in vec4 position;
layout (location = 4) in vec2 tc;
out vec2 outtc;

void main(void)
{
    outtc = tc;
	gl_Position = vec4(position.xyz, 1.0); 
}
