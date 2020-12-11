#include "Renderable.h"

Renderable::Renderable() {}

Renderable::~Renderable() {
	delete mesh;
	delete texture;
}

void Renderable::setMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void Renderable::setTexture(Texture* texture, float tiling) {
	this->texture = texture;
	this->textureTiling = tiling;
}

Mesh* Renderable::getMesh() {
	return mesh;
}

Texture* Renderable::getTexture() {
	return texture;
}

float Renderable::getTextureTiling() {
	return textureTiling;
}