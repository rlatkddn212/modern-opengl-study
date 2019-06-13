#version 420 core

layout (location = 0) in vec4 position;
layout(location = 1) in vec4 color;
// �ٸ� ���̴��� �����Ѵ�.
out vec4 out_color;

void main(void)
{
	gl_Position = vec4(position.xyz, 1.0); 

	out_color = color;
}
