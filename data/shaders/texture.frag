#version 330

// Inputs
in vec3 cameraSpacePosition;
in vec3 vertexNormal;

// Lighting parameters
uniform vec3 sunPosition;
uniform vec4 sunIntensity;
uniform vec4 ambientIntensity;
uniform vec4 diffuseColor;
uniform float attenuationFactor;

// Textures
uniform sampler2D testTexture;

// Output
out vec4 outputColor;

vec4 applyLightIntensity(in vec3 cameraSpacePosition, out vec3 dirToLightSource)
{
    vec3 lightDifference =  sunPosition - cameraSpacePosition;
    float lightDistanceSqr = dot(lightDifference, lightDifference);
    dirToLightSource = lightDifference * inversesqrt(lightDistanceSqr);
    
    return sunIntensity / ( 1.0 + attenuationFactor * lightDistanceSqr);
}

void main()
{
    vec3 dirToSun = vec3(0.0);
    vec4 attenIntensity = applyLightIntensity(cameraSpacePosition, dirToSun);
    float cosAI_sun = clamp(dot(vertexNormal, dirToSun), 0, 1);

	vec2 texCoord;
	texCoord.s = cameraSpacePosition.x;
	texCoord.t = cameraSpacePosition.y;
	float c = texture(testTexture, texCoord).r;
	vec4 diffuseColor2 = diffuseColor + vec4(c, -c, -c, 0);

    // Output including ambient and diffuse lighting
    outputColor = diffuseColor2 * ambientIntensity
            + diffuseColor2 * attenIntensity * cosAI_sun;
}