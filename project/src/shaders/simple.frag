// Fragment Shader 

#version 400

in DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
	float alpha;
	vec3 toLightVector;
} In;

struct DirectionalLight {
	vec3 color;
	float intensity;
	vec3 direction;
};

uniform DirectionalLight directionalLight;
uniform sampler2D textureSampler;

uniform vec3 lightColor;

out vec4 outColor;

vec4 CalculateAmbientColor() {
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.intensity;

	return ambientColor;
}
vec4 CalculateDiffuseColor() {
	float diffuseFactor = dot(normalize(In.normal), -directionalLight.direction);
	diffuseFactor = max(0.0f, diffuseFactor);
	vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.intensity * diffuseFactor;

	return diffuseColor;
}

void main() {
	if (In.alpha <= 0) {
		discard;
	}
	vec4 ambientColor = CalculateAmbientColor();
	vec4 diffuseColor = CalculateDiffuseColor();
	vec4 textureColor = texture(textureSampler, In.textureCoord);

	outColor = textureColor * (ambientColor + diffuseColor);


	// remove transparent pixels
	if (textureColor.a < 0.5) {
		discard;
	}

	vec3 unitNormal = normalize(In.normal);
	vec3 unitLightVector = normalize(In.toLightVector);

	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(0.3, nDotl);
	vec3 diffuse = brightness * lightColor;

	outColor = vec4(diffuse, 1.0) * textureColor;
	outColor = mix(vec4(1,1,1,1), outColor, In.alpha);
}
