#version 400

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;

out DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
	float alpha;
	vec3 toLightVector;
} Out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float lodEnabled;
uniform vec3 skyColor;
uniform vec4 clipPlane;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform float textureTiling;

const float threshold = 1000 * 1000;

void main() {
	vec4 worldPosition = model * position;
	vec4 positionRelativeToCamera = view * worldPosition;
	gl_Position = projection * positionRelativeToCamera;

	gl_ClipDistance[0] = dot(worldPosition, clipPlane);

	if (lodEnabled == 1.f) {
		vec3 toCameraVector = cameraPosition - worldPosition.xyz;
		float sq_dist = dot(toCameraVector, toCameraVector);
		sq_dist = clamp(sq_dist, 0, threshold);
		Out.alpha = 1 - (sq_dist / threshold);
	} else {
		Out.alpha = 1;
	}
	Out.worldPosition = worldPosition.xyz;
	Out.textureCoord = textureCoord * textureTiling;
	Out.normal = (model * vec4(normal, 0.0f)).xyz;
	Out.toLightVector = lightPosition - worldPosition.xyz;
}
