#version 420 core

layout (location = 0) in vec4 position;
uniform mat4 mvp_matrix;

out VERTEX_OUT
{
	vec4 color;
}vs_out;

void main(void)
{
	gl_Position = mvp_matrix * vec4(position.xyz, 1.0);
	vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}
