#version 400

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D guiTexture;

void main(void){

	out_Color = texture(guiTexture,textureCoords);
	out_Color = mix(out_Color, vec4(0,0,1,1), 0.4);

}