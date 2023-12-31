#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D spriteTexture;

uniform float transparent;

void main()
{
	outColor = texture(spriteTexture, inTexCoords);
	outColor.a *= transparent;
}