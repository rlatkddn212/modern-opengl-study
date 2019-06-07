#version 430 core
// vertex.glsl과 같은 이름을 사용해야한다.
in vec4 out_color;
out vec4 color;

void main()
{
	color = out_color;
}