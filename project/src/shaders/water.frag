#version 400 core

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;

out vec4 out_Color;

uniform sampler2D reflectionSampler;
uniform sampler2D refractionSampler;
uniform sampler2D dudvSampler;

uniform float moveFactor;

const float waveStrength = 0.004;

void main() {
	vec2 ndc = (clipSpace.xy / clipSpace.w)/2.0 + 0.5;
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

	vec2 distortion1 = (texture(dudvSampler, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 2.0 - 1) * waveStrength;
	vec2 distortion2 = (texture(dudvSampler, vec2(-textureCoords.x + moveFactor, textureCoords.y + moveFactor)).rg * 2.0 - 1) * waveStrength;
	vec2 totalDistortion = distortion1 + distortion2;

	refractTexCoords += totalDistortion;
	refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);

	reflectTexCoords += totalDistortion;
	reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
	reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);

	vec4 reflectColor = texture(reflectionSampler, reflectTexCoords);
	vec4 refractColor = texture(refractionSampler, refractTexCoords);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = dot(viewVector, vec3(0,1,0)); //asume water normal to be y
	//refractiveFactor = pow(refractiveFactor, 10);

	out_Color = mix(reflectColor, refractColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0,0,1,1), 0.2);
	//out_Color = vec4(ndc,0,1);
	//out_Color = vec4(refractTexCoords,0,1);
	//out_Color = vec4(0,1,0,1.0);
}
