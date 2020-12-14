#version 400

layout (location = 0) in vec2 position;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPosition;

void main() {
	vec4 worldPosition = model * vec4(position.x, 4, position.y, 1);
	clipSpace = projection * view * worldPosition;
	gl_Position = clipSpace;
	textureCoords = vec2(position.x/2.0 + 0.5, position.y/2.0+ 0.5); //* tiling
	toCameraVector = cameraPosition - worldPosition.xyz;
}