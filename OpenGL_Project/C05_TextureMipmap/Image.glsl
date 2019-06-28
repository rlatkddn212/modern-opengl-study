#version 430 core
out vec4 color;
in vec2 texCoord;
layout(binding = 0) uniform sampler2D image01;
layout(binding = 1) uniform sampler2D image02;
uniform int texID;

void main()
{
	if (texID % 2 == 0)
	{
		color = texture(image01, texCoord);
	}
	else
	{
		color = texture(image02, texCoord);
	}
}