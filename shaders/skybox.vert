#version 400

layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec4 clipPlane;

void main() {
	vec4 worldPosition = model * vec4(position, 1.0);
	gl_Position = projection * view * worldPosition;

	gl_ClipDistance[0] = dot(worldPosition, clipPlane);
}
