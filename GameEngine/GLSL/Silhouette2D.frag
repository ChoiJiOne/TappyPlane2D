#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D spriteTexture;

uniform vec3 silhouetteRGB;
uniform float transparent;

void main()
{
	vec4 colorRGBA = texture(spriteTexture, inTexCoords);
	outColor = vec4(silhouetteRGB, colorRGBA.a);
	outColor.a *= transparent;
}