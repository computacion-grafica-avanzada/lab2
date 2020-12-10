#pragma once
#include "Mesh.h"

static const unsigned int MAX_JOINTS = 50;

class AnimatedMesh :
	public Mesh
{
public:
	AnimatedMesh(
		std::vector<glm::vec4> vertices,
		std::vector<glm::vec2> uvs,
		std::vector<glm::vec3> normals,
		std::vector<glm::uvec4> jointIds,
		std::vector<glm::vec4> jointWeights,
		std::vector<unsigned int> indices
	);
	~AnimatedMesh();
};

