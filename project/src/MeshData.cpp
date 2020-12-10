#include "MeshData.h"

MeshData::MeshData(float* vertices, float* textureCoords, float* normals, int* indices, int* jointIds, float* vertexWeights, int verticesCount) {
	this->vertices = vertices;
	this->textureCoords = textureCoords;
	this->normals = normals;
	this->indices = indices;
	this->jointIds = jointIds;
	this->vertexWeights = vertexWeights;
	this->vertexCount = verticesCount / DIMENSIONS;
}