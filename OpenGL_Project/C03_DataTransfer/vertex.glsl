#version 430 core

// glVertexAttri �Լ��� ���� ���� �޴´�.
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 attr;
layout(location = 2) in vec4 color;

// �ٸ� ���̴��� �����Ѵ�.
out vec4 out_color;

void main()
{
	gl_Position = vec4(position.xyz, 1.0) + attr;

	out_color = color;
}
