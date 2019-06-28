#version 430 core
out vec4 color;
in vec2 texCoord;
layout(binding = 0) uniform sampler2D image01;
layout (binding = 1) uniform sampler2D image02;

void main()
{
	color = mix(texture(image01, texCoord), texture(image02, texCoord), 0.5);
}