#version 330 core

//values from vertex shader
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 fragmentColor;

//output data
out vec3 color;

//constant values
uniform mat4 MVP;
uniform vec3 LightPosition_worldspace;
uniform float LightPower;
uniform float SpecLobeMod;

void main() {
	//Light emission properties
	vec3 LightColor = vec3(0.9, 0.5, 0.1);
	//float LightPower = 1.0f;

	vec3 MaterialDiffuseColor = vec3(0.1, 0.1, 0.1);
	vec3 MaterialAmbientColor = fragmentColor * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.7, 0.7, 0.7);

	//dist to light
	float distance = length(LightPosition_worldspace - Position_worldspace);

	//Normal of computed fragment
	vec3 n = normalize(Normal_cameraspace);
	//direction from frag to light
	vec3 l = normalize(LightDirection_cameraspace);
	//cos of angle between normal and light dir
	float cosTheta = clamp(dot(n, l), 0, 1);

	//Eye vector towards cam
	vec3 E = normalize(EyeDirection_cameraspace);
	//reflection direction
	vec3 R = reflect(-l, n);
	//Cosine of angle between eye v and r v
	float cosAlpha = clamp(dot(E, R), 0, 1);

	color =
		//Ambient simulates indirect lighting
		MaterialAmbientColor +
		//Diffuse = color
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		//Specular = reflective highlight
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 4) / (distance * distance);

	//keep this line vvv
	//color = fragmentColor;
}