#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D spriteTexture;

uniform vec3 silhouetteRGB;
uniform float transparent;

const int WEIGHT_SIZE = 5;
float WEIGHTS[WEIGHT_SIZE] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
// 1. First
//	float colorA = texture(spriteTexture, inTexCoords).a;
//	vec3 colorRGB = silhouetteRGB;
//
//	outColor = vec4(colorRGB, colorA);
//	outColor.a *= transparent;

// 2. Second
	vec2 offset = 1.0f / textureSize(spriteTexture, 0);
	vec3 colorRGB = silhouetteRGB;

	float colorA = texture(spriteTexture, inTexCoords).a * WEIGHTS[0];

	for(int i = 1; i < WEIGHT_SIZE; ++i)
	{
		colorA += texture(spriteTexture, inTexCoords + vec2(offset.x * i, 0.0f)).a * WEIGHTS[i];
		colorA += texture(spriteTexture, inTexCoords - vec2(offset.x * i, 0.0f)).a * WEIGHTS[i];
		colorA += texture(spriteTexture, inTexCoords + vec2(0.0f, offset.y * i)).a * WEIGHTS[i];
		colorA += texture(spriteTexture, inTexCoords - vec2(0.0f, offset.y * i)).a * WEIGHTS[i];
	}
		
	outColor = vec4(colorRGB, colorA);
	outColor.a *= transparent;
}