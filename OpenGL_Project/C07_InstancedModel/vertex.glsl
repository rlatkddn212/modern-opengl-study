#version 430 core

layout (location = 0) in vec3 position;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 offset;
uniform mat4 mvp_matrix;

out vec2 texCoord;
out flat int layer;

void main(void)
{
	gl_Position = mvp_matrix * vec4(position + offset,1.0);
	texCoord = tex;
	layer = gl_InstanceID;
}