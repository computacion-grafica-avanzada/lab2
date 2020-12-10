#pragma once

#include <glm/glm.hpp>

#include <vector>
#include "buffers/Buffer.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"

class Mesh {

	std::vector<glm::vec4> vertices;
	//std::vector<glm::vec2> uvs;
	//std::vector<glm::vec3> normals;
	//std::vector<unsigned int> indices;

	VertexArray* vertexArray;
	IndexBuffer* indexBuffer;

public:
	Mesh(
		std::vector<glm::vec4> vertices,
		std::vector<glm::vec2> uvs,
		std::vector<glm::vec3> normals,
		std::vector<unsigned int> indices
	);
	~Mesh();

	std::vector<glm::vec4> getVertices();
	VertexArray* getVertexArray();
	IndexBuffer* getIndexBuffer();
};
