#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

out vec4 fragColor;

void main()
{
	gl_Position = cameraToClipMatrix * modelToCameraMatrix * position;
	fragColor = color;
}
