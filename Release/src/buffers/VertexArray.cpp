#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &arrayID);
}

VertexArray::~VertexArray() {
	for (Buffer* buffer : buffers) delete buffer;
	buffers.clear();
	glDeleteVertexArrays(1, &arrayID);
}

void VertexArray::addBuffer(Buffer* buffer, GLuint index) {
	// add buffer to vao
	bind();
	buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer->unbind();
	unbind();

	// save vbo in vector
	buffers.push_back(buffer);
}

void VertexArray::bind() {
	glBindVertexArray(arrayID);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}