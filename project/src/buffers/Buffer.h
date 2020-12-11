#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Buffer {
private:
	GLuint bufferID;
	GLsizei componentCount;
public:
	Buffer(GLfloat* data, GLsizei count, GLsizei componentCount);
	Buffer(const std::vector<glm::vec2>& data);
	Buffer(const std::vector<glm::vec3>& data);
	Buffer(const std::vector<glm::vec4>& data);
	Buffer(const std::vector<glm::uvec3>& data);

	~Buffer();

	void bind();
	void unbind();

	GLsizei getComponentCount();
};