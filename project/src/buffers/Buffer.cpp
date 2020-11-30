#include "Buffer.h"

Buffer::Buffer(GLfloat* data, GLsizei count, GLsizei componentCount) {
	glGenBuffers(1, &bufferID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
	unbind();
}

Buffer::Buffer(const std::vector<glm::vec2>& data) : componentCount(2) {
	glGenBuffers(1, &bufferID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), data.data(), GL_STATIC_DRAW);
	unbind();
}

Buffer::Buffer(const std::vector<glm::vec3>& data) : componentCount(3) {
	glGenBuffers(1, &bufferID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);
	unbind();
}

Buffer::Buffer(const std::vector<glm::vec4>& data) : componentCount(4) {
	glGenBuffers(1, &bufferID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec4), data.data(), GL_STATIC_DRAW);
	unbind();
}

Buffer::~Buffer() {
	glDeleteBuffers(1, &bufferID);
}

void Buffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void Buffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLsizei Buffer::getComponentCount() {
	return componentCount;
}