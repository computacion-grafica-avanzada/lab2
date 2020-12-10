#include "Vertex.h"

Vertex::Vertex(int index, glm::vec3 position, VertexSkinData weightsData) {
	this->index = index;
	this->weightsData = weightsData;
	this->position = position;
	this->length = position.length();
}

VertexSkinData Vertex::getWeightsData() {
	return weightsData;
}

void Vertex::addTangent(glm::vec3 tangent) {
	tangents.push_back(tangent);
}

void Vertex::averageTangents() {
	if (tangents.size() == 0) {
		return;
	}
	for (glm::vec3 tangent : tangents) {
		averagedTangent += tangent;
	}
	averagedTangent = glm::normalize(averagedTangent);
}

bool Vertex::isSet() {
	return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}

bool Vertex::hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther) {
	return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
}

glm::vec3 Vertex::getPosition() {
	return position;
}

void Vertex::setTextureIndex(int textureIndex) {
	this->textureIndex = textureIndex;
}

int Vertex::getTextureIndex() {
	return textureIndex;
}

void Vertex::setNormalIndex(int normalIndex) {
	this->normalIndex = normalIndex;
}

int Vertex::getNormalIndex() {
	return normalIndex;
}

void Vertex::setDuplicateVertex(Vertex* duplicateVertex) {
	this->duplicateVertex = duplicateVertex;
}

Vertex* Vertex::getDuplicateVertex() {
	return duplicateVertex;
}

int Vertex::getIndex() {
	return index;
}

float Vertex::getLength() {
	return length;
}

glm::vec3 Vertex::getAverageTangent() {
	return averagedTangent;
}

VertexSkinData Vertex::getWeightsData() {
	return weightsData;
}

