#version 400

layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec2 inTextureCoord;
layout (location = 2) in vec3 inNormal;

out vec4 clipSpace;
out vec2 textureCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	clipSpace = projection * view * model * inPosition; //vec4(inPosition.x, 0.0, inPosition.z, 1.0);
	gl_Position = clipSpace;
	textureCoords = vec2(inPosition.x/2.0 + 0.5, inPosition.z/2.0+ 0.5); //* tiling
}