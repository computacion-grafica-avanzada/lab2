#pragma once

#include <vector>
#include <glm/glm.hpp>

/* This object contains all the mesh data for an animated model that is to be loaded into the VAO. */
class MeshData
{
public:
	const int DIMENSIONS = 3;

	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::uvec3> jointIds;
	std::vector<glm::vec3> vertexWeights;
	std::vector<unsigned int> indices;
	int vertexCount;

	MeshData(std::vector<glm::vec4> vertices, std::vector<glm::vec2> textureCoords, std::vector<glm::vec3> normals,
		std::vector<glm::uvec3>jointIds, std::vector<glm::vec3> vertexWeights, std::vector<unsigned int> indices, int verticesCount);
};

