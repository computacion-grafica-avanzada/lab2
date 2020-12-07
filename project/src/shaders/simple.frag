// Fragment Shader 

#version 400

in DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
	float alpha;
} In;

struct DirectionalLight {
	vec3 color;
	float intensity;
	vec3 direction;
};

uniform DirectionalLight directionalLight;
uniform sampler2D textureSampler;

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

	outColor = mix(vec4(1,1,1,1), textureColor, In.alpha);
	//outColor = vec4(0,In.alpha,0,In.alpha);
	//outColor = vec4(In.worldPosition,1);
}
