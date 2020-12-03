#include "Water.h"

Water::Water() {
	textureTiling = 1;
	moveFactor = 0;
	moveSpeed = 1.0f / 40.0f;
	distortionStrength = 0.04f;
	specularPower = 20.0f;
}

Water::~Water() {}

void Water::setMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void Water::setShader(Shader* shader) {
	this->shader = shader;
}

void Water::setDUDV(Texture* texture) {
	this->dudv = texture;
}
void Water::setNormal(Texture* texture) {
	this->normal = texture;
}

Mesh* Water::getMesh() {
	return mesh;
}

Shader* Water::getShader() {
	return shader;
}

Texture* Water::getDUDV() {
	return dudv;
}

Texture* Water::getNormal() {
	return normal;
}

float Water::getMoveFactor() {
	return moveFactor;
}

//Transform* Water::getTransform() {
//	return transform;
//}