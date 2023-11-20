#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D framebuffer;

const int NONE_EFFECT = 0;
const int INVERSION_EFFECT = 1;
const int AVERAGE_GRAYSCALE = 2;
const int WEIGHT_GRAYSCALE = 3;
const int NORMAL_BLUR = 4;

uniform int effectOption;
uniform float blurBias;

vec3 CalculateNormalBlur(float bias);

void main()
{
	vec3 colorRGB = vec3(0.0f);

	switch(effectOption)
	{
	case NORMAL_BLUR:
		colorRGB = CalculateNormalBlur(blurBias);
		break;

	case WEIGHT_GRAYSCALE:
		colorRGB = texture(framebuffer, inTexCoords).rgb;
		float weight = 0.2126 * colorRGB.r + 0.7152 * colorRGB.g + 0.0722 * colorRGB.b;
		colorRGB = vec3(weight, weight, weight);
		break;

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

vec3 CalculateNormalBlur(float bias)
{
	float offset = 1.0f / bias;

	vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2(   0.0f,  offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,    0.0f), // center-left
        vec2(   0.0f,    0.0f), // center-center
        vec2( offset,    0.0f), // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(   0.0f, -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

    float kernel[9] = float[](
        1.0 / 16.0f, 2.0 / 16.0f, 1.0 / 16.0f,
        2.0 / 16.0f, 4.0 / 16.0f, 2.0 / 16.0f,
        1.0 / 16.0f, 2.0 / 16.0f, 1.0 / 16.0f
    );

	vec3 sampleRGB[9];
    for(int i = 0; i < 9; i++)
    {
        sampleRGB[i] = texture(framebuffer, inTexCoords.st + offsets[i]).rgb;
    }

    vec3 colorRGB = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        colorRGB += sampleRGB[i] * kernel[i];
    }

	return colorRGB;
}