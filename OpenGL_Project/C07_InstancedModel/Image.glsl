#version 430 core

out vec4 color;
in vec2 texCoord;
layout (binding=0) uniform sampler2DArray textureArray;
in flat int layer;

void main(void)
{
	color = texture(textureArray, vec3(texCoord.x, texCoord.y, layer) );
}