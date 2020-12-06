#include "Mesh.h"

Mesh::Mesh(
	std::vector<glm::vec4> vertices, 
	std::vector<glm::vec2> uvs, 
	std::vector<glm::vec3> normals, 
	std::vector<unsigned int> indices
) {
	this->vertices = vertices;

	Buffer* vertexBuffer = new Buffer(vertices);
	Buffer* uvBuffer = new Buffer(uvs);
	Buffer* normalBuffer = new Buffer(normals);

	vertexArray = new VertexArray();
	vertexArray->addBuffer(vertexBuffer, 0);
	vertexArray->addBuffer(uvBuffer, 1);
	vertexArray->addBuffer(normalBuffer, 2);

	indexBuffer = new IndexBuffer(indices);
}

Mesh::~Mesh() {
	delete vertexArray;
	delete indexBuffer;
}

std::vector<glm::vec4> Mesh::getVertices() {
	return vertices;
}

VertexArray* Mesh::getVertexArray() {
	return vertexArray;
}

IndexBuffer* Mesh::getIndexBuffer() {
	return indexBuffer;
}
