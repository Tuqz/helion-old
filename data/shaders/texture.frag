#version 330

// Inputs
in vec3 cameraSpacePosition;
in vec3 vertexNormal;
in vec2 texCoords;

// Lighting parameters
uniform vec3 sunPosition;
uniform vec4 sunIntensity;
uniform vec4 ambientIntensity;
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

	vec4 diffuseColor = texture(testTexture, texCoords);
	//vec4 diffuseColor = vec4(texCoords,0,1);

    // Output including ambient and diffuse lighting
    //outputColor = diffuseColor * ambientIntensity
    //        + diffuseColor * attenIntensity * cosAI_sun;
	outputColor = diffuseColor;
}