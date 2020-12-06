#version 400

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPosition;

void main() {
	vec4 worldPosition = model * position;
	clipSpace = projection * view * worldPosition; //vec4(position.x, 0.0, position.z, 1.0);
	gl_Position = clipSpace;
	textureCoords = vec2(position.x/2.0 + 0.5, position.z/2.0+ 0.5); //* tiling
	toCameraVector = cameraPosition - worldPosition.xyz;
}