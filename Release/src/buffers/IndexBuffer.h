#pragma once

#include <glad/glad.h>
#include <vector>
#include "Buffer.h"

class IndexBuffer {
private:
	GLuint bufferID;
	GLsizei count;
public:
	IndexBuffer(GLuint* data, GLsizei count);
	IndexBuffer(const std::vector<unsigned int>& data);
	~IndexBuffer();
	void bind();
	void unbind();
	GLsizei getCount();
};