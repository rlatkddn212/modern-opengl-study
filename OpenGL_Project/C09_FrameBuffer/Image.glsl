#version 430 core
out vec4 color;
in vec2 texCoord;
uniform sampler2D image;

void main()
{
	color = texture(image, texCoord);
}