#version 400 core

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;
in vec3 fromLightVector;

out vec4 outColor;

uniform sampler2D reflectionSampler;
uniform sampler2D refractionSampler;
uniform sampler2D dudvSampler;
uniform sampler2D normalSampler;
uniform sampler2D depthSampler;

uniform float moveFactor;
uniform float near;
uniform float far;
uniform vec3 lightColor;

//const float waveStrength = 0.004;
//const float shineDamper = 20.0;
//const float reflectivity = 0.6;

const float waveStrength = 0.04;
const float shineDamper = 20.0;
const float reflectivity = 0.5;

void main() {
	vec2 ndc = (clipSpace.xy / clipSpace.w)/2.0 + 0.5;
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

	float depth = texture(depthSampler, refractTexCoords).r;
	float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	depth = gl_FragCoord.z;
	float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	float waterDepth = floorDistance - waterDistance;

	vec2 distortedTexCoords = texture(dudvSampler, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y + moveFactor);
	vec2 totalDistortion = (texture(dudvSampler, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength * clamp(waterDepth/500.0, 0.0, 1.0);;

	//vec2 distortion1 = (texture(dudvSampler, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 2.0 - 1) * waveStrength;
	//vec2 distortion2 = (texture(dudvSampler, vec2(-textureCoords.x + moveFactor, textureCoords.y + moveFactor)).rg * 2.0 - 1) * waveStrength;
	//vec2 totalDistortion = distortion1 + distortion2;

	refractTexCoords += totalDistortion;
	refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);

	reflectTexCoords += totalDistortion;
	reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
	reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);

	vec4 reflectColor = texture(reflectionSampler, reflectTexCoords);
	vec4 refractColor = texture(refractionSampler, refractTexCoords);

	vec4 normalMapColor = texture(normalSampler, distortedTexCoords);
	vec3 normal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b * 3, normalMapColor.g * 2.0 - 1.0);
	normal = normalize(normal);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = dot(viewVector, normal); //asume water normal to be y
	//refractiveFactor = pow(refractiveFactor, 10);


	vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
	float specular = max(dot(reflectedLight, viewVector), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = lightColor * specular * reflectivity * clamp(waterDepth/10.0, 0.0, 1.0);

	outColor = mix(reflectColor, refractColor, refractiveFactor);
	outColor = outColor + vec4(specularHighlights, 0.0);
	outColor.a = clamp(waterDepth/10.0, 0.0, 1.0);

	//outColor = mix(outColor, vec4(0,0,1,1), 0.02);
	//outColor = mix(vec4(skyColor,1), outColor, alpha);
	//outColor = vec4(0,alpha,0,1);
	//outColor = vec4(toCameraVector, 1);
	//outColor = normalMapColor;
	//outColor = vec4(waterDepth/100.0);
}
