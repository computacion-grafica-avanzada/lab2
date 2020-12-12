#version 400

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

void main()
{
    gl_FragColor = texture(diffuse, texCoord0);
		//*clamp(dot(-vec3(0, 0, 1), normal0), 0.0, 1.0);
}