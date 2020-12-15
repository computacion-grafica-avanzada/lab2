#version 400

out vec4 outColor;

uniform vec3 skyColorStart;
uniform vec3 skyColorEnd;
uniform float blendFactor;

void main() {
	vec3 skyColor = mix(skyColorStart, skyColorEnd, blendFactor);
	outColor = vec4(skyColor,1);
}
