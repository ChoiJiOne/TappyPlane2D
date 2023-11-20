#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D framebuffer;

const int NONE_EFFECT = 0;
const int INVERSION_EFFECT = 1;
const int AVERAGE_GRAYSCALE = 2;
const int WEIGHT_GRAYSCALE = 3;
const int NORMAL_BLUR = 4;
const int GAUSSIAN_BLUR = 5;

const int SAMPLES = 72;
const float TAU = 6.283185307179586476925286766559;

uniform int effectOption;
uniform float blurBias;

float Gaussian(float x);
vec3 CalculateNormalBlur(float bias);
vec3 CalculateGaussianBlur(float bias);

void main()
{
	vec3 colorRGB = vec3(0.0f);

	switch(effectOption)
	{
	case GAUSSIAN_BLUR:
		colorRGB = CalculateGaussianBlur(blurBias);
		break;

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

float Gaussian(float x) 
{
	float x2 = x * x;
	float width = 1.0f / sqrt(TAU * SAMPLES);

	return width * exp((x2 / (2.0f * SAMPLES)) * -1.0f);
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

// https://github.com/gdquest-demos/godot-shaders/blob/master/godot/Shaders/gaussian_blur.shader
vec3 CalculateGaussianBlur(float bias)
{
	vec2 size = 1.0f / textureSize(framebuffer, 0);
	vec2 scale = size * vec2(bias, bias);

	float totalWeight = 0.0;
	vec3 colorRGB = vec3(0.0);
	
	for (int i = -SAMPLES / 2; i < SAMPLES / 2; ++i) 
	{
		float weight = Gaussian(float(i));
		colorRGB += texture(framebuffer, inTexCoords.st + scale * vec2(float(i))).rgb * weight;
		totalWeight += weight;
	}
	
	return colorRGB / totalWeight;
}