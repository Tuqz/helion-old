#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoords;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

out vec3 cameraSpacePosition;
out vec3 vertexNormal;
out vec2 texCoords;

void main()
{
	vec4 cameraSpacePosition4 = modelToCameraMatrix * position;
	gl_Position = cameraToClipMatrix * cameraSpacePosition4;

	cameraSpacePosition = vec3(cameraSpacePosition4);
    vertexNormal = normalize(vec3(modelToCameraMatrix * vec4(normal, 0)));
    texCoords = textureCoords;
}