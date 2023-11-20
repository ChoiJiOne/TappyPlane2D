#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D spriteTexture;

uniform vec4 outlineRGBA;
uniform float transparent;

const vec2 offsets[8] = {
	vec2(-1.0f, -1.0f),
	vec2(-1.0f, +0.0f),
	vec2(-1.0f, +1.0f),
	vec2(+0.0f, -1.0f),
	vec2(+0.0f, +1.0f),
	vec2(+1.0f, -1.0f),
	vec2(+1.0f, +0.0f),
	vec2(+1.0f, +1.0f),
};

void main()
{
	vec2 size = 1.0f / textureSize(spriteTexture, 0);
	
	float outline = 0.0f;
	for(int index = 0; index < offsets.length(); ++index)
	{
		outline += texture(spriteTexture, inTexCoords + size * offsets[index]).a;
	}

	outline = min(outline, 1.0f);
	
	vec4 colorRGBA = texture(spriteTexture, inTexCoords);
	outColor = mix(colorRGBA, outlineRGBA, outline - colorRGBA.a);
	outColor.a *= transparent;
}