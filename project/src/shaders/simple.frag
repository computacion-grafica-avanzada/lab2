// Fragment Shader 

#version 400

in DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
	float alpha;
	vec4 test;
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

	vec3 lala = normalize(vec3(In.test[0], In.test[1], In.test[2]));
	// if(In.test[0] == 0)
	// {
	// 	lala = vec3(1.0, 0, 0);
	// }
	// else 
	// {
	// 	lala = vec3(0, 1.0, 0);
	// }

	outColor = mix(vec4(1,1,1,1), textureColor, In.alpha);
	//outColor = vec4(0,In.alpha,0,In.alpha);
	// outColor = vec4(lala,1);
}
