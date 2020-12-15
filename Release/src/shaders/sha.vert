#version 400 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec2 in_Color;
layout (location = 2) in vec3 in_Normal;

out vec3 vertex_color;

void main(void){
    mat4 MVP = projection * view * model;
	gl_Position = MVP * in_Position;
	vertex_color = vec3(in_Color,1.0);
}