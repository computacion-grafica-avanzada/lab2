#include "MeshData.h"

MeshData::MeshData(std::vector<glm::vec4> vertices, std::vector<glm::vec2> textureCoords, std::vector<glm::vec3> normals,
	std::vector<glm::uvec3>jointIds, std::vector<glm::vec3> vertexWeights, std::vector<unsigned int> indices, int verticesCount) {
	this->vertices = vertices;
	this->textureCoords = textureCoords;
	this->normals = normals;
	this->indices = indices;
	this->jointIds = jointIds;
	this->vertexWeights = vertexWeights;
	this->vertexCount = verticesCount / DIMENSIONS;
}