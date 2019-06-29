#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;
uniform mat4 mvp_matrix;

out vec2 texCoord;

void main(void)
{
	gl_Position = mvp_matrix * vec4(position,1.0);
	texCoord = tex;
}