#pragma once

#include <glad/glad.h>
#include <vector>
#include "Buffer.h"

class VertexArray {
private:
	GLuint arrayID;
	std::vector<Buffer*> buffers;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(Buffer* buffer, GLuint index);
	void bind();
	void unbind();
};