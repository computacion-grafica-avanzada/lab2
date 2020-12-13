#version 400

in vec3 textureCoords;
out vec4 outColor;

uniform samplerCube cubeMap;
uniform vec3 skyColorStart;
uniform vec3 skyColorEnd;
uniform float blendFactor;

void main() {
	outColor = texture(cubeMap, textureCoords);
	vec3 skyColor = mix(skyColorStart, skyColorEnd, blendFactor);
	outColor = vec4(skyColor,1);
}