// Fragment Shader 

#version 400

in DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
	float alpha;
	vec3 toLightVector;
} In;

uniform vec3 skyColor;
uniform vec3 lightColor;
uniform sampler2D textureSampler;

out vec4 outColor;

void main() {
	if (In.alpha <= 0) {
		discard;
	}

	vec4 textureColor = texture(textureSampler, In.textureCoord);
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
	outColor = mix(vec4(skyColor,1), outColor, In.alpha);
}
