#version 430 core

// glVertexAttri 함수를 통해 전달 받는다.
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 attr;
layout(location = 2) in vec4 color;

// 다른 쉐이더로 전달한다.
out vec4 out_color;

void main()
{
	gl_Position = vec4(position.xyz, 1.0) + attr;

	out_color = color;
}
