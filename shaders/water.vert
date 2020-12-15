#version 400

layout (location = 0) in vec2 position;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;
out vec3 fromLightVector;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;

void main() {
	vec4 worldPosition = model * vec4(position.x, 4, position.y, 1);
	clipSpace = projection * view * worldPosition;
	gl_Position = clipSpace;
	textureCoords = vec2(position.x/2.0 + 0.5, position.y/2.0+ 0.5) * 4;// tiling
	toCameraVector = cameraPosition - worldPosition.xyz;
	fromLightVector = worldPosition.xyz - lightPosition;
}