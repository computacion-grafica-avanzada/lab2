// Vertex Shader

#version 400

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec2 inTextureCoord;
layout (location = 2) in vec3 inNormal;

out DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
	float alpha;
    vec4 test;
} Out;

uniform vec4 clipPlane;
uniform float textureTiling;
uniform vec3 cameraPosition;

const float threshold = 1000 * 1000;

void main() {
	vec4 worldPosition = model * inPosition;
	vec4 positionRelativeToCamera = view * worldPosition;
	
	gl_Position = projection * positionRelativeToCamera;

	vec3 diff = worldPosition.xyz - cameraPosition;
	float sq_dist = dot(diff, diff);
	sq_dist = clamp(sq_dist, 0, threshold);
	gl_ClipDistance[0] = dot(worldPosition, clipPlane);
	
	Out.alpha = 1 - (sq_dist / threshold);
	Out.worldPosition = worldPosition.xyz;
	Out.textureCoord = inTextureCoord * textureTiling;
	Out.normal = (model * vec4(inNormal, 0.0f)).xyz;
}
