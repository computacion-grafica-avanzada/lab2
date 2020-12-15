#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLuint* data, GLsizei count) : count(count) {
	glGenBuffers(1, &bufferID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	unbind();
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data) {
	count = data.size();
	glGenBuffers(1, &bufferID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data.data(), GL_STATIC_DRAW);
	unbind();
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &bufferID);
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLsizei IndexBuffer::getCount() {
	return count;
}