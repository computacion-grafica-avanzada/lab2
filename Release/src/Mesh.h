#pragma once

#include <glm/glm.hpp>

#include <vector>
#include "buffers/Buffer.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "Shader.h"
#include "Texture.h"

class Mesh {
	//std::vector<glm::vec4> vertices;
	//std::vector<glm::vec2> uvs;
	//std::vector<glm::vec3> normals;
	//std::vector<unsigned int> indices;

	VertexArray* vertexArray;
	IndexBuffer* indexBuffer;
	Texture* texture;
	Shader* shader;
public:
	Mesh(
		std::vector<glm::vec4> vertices, 
		std::vector<glm::vec2> uvs, 
		std::vector<glm::vec3> normals, 
		std::vector<unsigned int> indices,
		Texture* texture
	);
	~Mesh();

	VertexArray* getVertexArray();
	IndexBuffer* getIndexBuffer();
	Texture* getTexture();
	void setShader(Shader* shader);
	Shader* getShader();
};
