#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(
	std::vector<glm::vec4> vertices,
	std::vector<glm::vec2> uvs,
	std::vector<glm::vec3> normals,
	std::vector<glm::uvec3> jointIds,
	std::vector<glm::vec3> jointWeights,
	std::vector<unsigned int> indices
) : Mesh(vertices, uvs, normals, indices) {

	Buffer* jointIdsBuffer = new Buffer(jointIds);
	Buffer* jointWeightsBuffer = new Buffer(jointWeights);

	getVertexArray()->addBuffer(jointIdsBuffer, 3);
	getVertexArray()->addBuffer(jointWeightsBuffer, 4);
}

AnimatedMesh::~AnimatedMesh() {
}

