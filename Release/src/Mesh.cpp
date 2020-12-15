#include "Mesh.h"

Mesh::Mesh(
	std::vector<glm::vec4> vertices, 
	std::vector<glm::vec2> uvs, 
	std::vector<glm::vec3> normals, 
	std::vector<unsigned int> indices,
	Texture* texture
) {

	Buffer* vertexBuffer = new Buffer(vertices);
	Buffer* uvBuffer = new Buffer(uvs);
	Buffer* normalBuffer = new Buffer(normals);

	vertexArray = new VertexArray();
	vertexArray->addBuffer(vertexBuffer, 0);
	vertexArray->addBuffer(uvBuffer, 1);
	vertexArray->addBuffer(normalBuffer, 2);

	indexBuffer = new IndexBuffer(indices);
	this->texture = texture;

	this->shader = new Shader("./src/shaders/simple.vert", "./src/shaders/simple.frag");
}

Mesh::~Mesh() {
	delete vertexArray;
	delete indexBuffer;
}

VertexArray* Mesh::getVertexArray() {
	return vertexArray;
}

IndexBuffer* Mesh::getIndexBuffer() {
	return indexBuffer;
}

Texture* Mesh::getTexture() {
	return texture;
}

void Mesh::setShader(Shader* shader) {
	this->shader = shader;
}

Shader* Mesh::getShader() {
	return shader;
}