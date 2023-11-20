#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D framebuffer;

const int NONE_EFFECT = 0;
const int INVERSION_EFFECT = 1;
const int AVERAGE_GRAYSCALE = 2;

uniform int effectOption;

void main()
{
	vec3 colorRGB = vec3(0.0f);

	switch(effectOption)
	{
	case AVERAGE_GRAYSCALE:
		colorRGB = texture(framebuffer, inTexCoords).rgb;
		float average = (colorRGB.r + colorRGB.g, colorRGB.b) / 3.0f;
		colorRGB = vec3(average, average, average);
		break;

	case INVERSION_EFFECT:
		colorRGB = 1.0f - texture(framebuffer, inTexCoords).rgb;
		break;
	
	case NONE_EFFECT:
		colorRGB = texture(framebuffer, inTexCoords).rgb;
		break;
	}

	outColor = vec4(colorRGB, 1.0f);
}