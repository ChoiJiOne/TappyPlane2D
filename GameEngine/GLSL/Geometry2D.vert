#version 460 core

layout(location = 0) in vec3 inPosition;
//layout(location = 1) in vec4 inColor;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(inPosition, 1.0f);
}