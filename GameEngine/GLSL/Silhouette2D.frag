#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D spriteTexture;

uniform vec3 silhouetteRGB;
uniform float transparent;

void main()
{
	float colorA = texture(spriteTexture, inTexCoords).a;
	vec3 colorRGB = silhouetteRGB;

	outColor = vec4(colorRGB, colorA);
	outColor.a *= transparent;
}