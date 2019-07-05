#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 normal;
uniform mat4 mvp_matrix;

out VERTEX_OUT
{
	vec2 vt;
}vs_out;

void main(void)
{
	gl_Position = mvp_matrix * vec4(position, 1.0);
	vs_out.vt = tex;
}
