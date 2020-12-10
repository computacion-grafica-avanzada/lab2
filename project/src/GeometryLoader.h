#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tinyxml2.h>
#include <string>

#include "Vertex.h"
#include "MeshData.h"
#include "XMLUtils.h"

class GeometryLoader
{
	const glm::mat4 CORRECTION = glm::rotate(glm::identity<glm::mat4>(), glm::radians(-90.0f), glm::vec3(1, 0, 0));

	tinyxml2::XMLElement* meshData;

	std::vector<VertexSkinData> vertexWeights;

	float* verticesArray;
	float* normalsArray;
	float* texturesArray;
	int* indicesArray;
	int* jointIdsArray;
	float* weightsArray;

	std::vector<Vertex*> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;

	void readRawData();
	void readPositions();
	void readNormals();
	void readTextureCoords();
	void assembleVertices();
	Vertex* processVertex(int posIndex, int normIndex, int texIndex);
	int* convertIndicesListToArray();
	float convertDataToArrays();
	Vertex* dealWithAlreadyProcessedVertex(Vertex* previousVertex, int newTextureIndex, int newNormalIndex);
	void initArrays();
	void removeUnusedVertices();

public:
	GeometryLoader(tinyxml2::XMLElement* geometryNode, std::vector<VertexSkinData> vertexWeights);
	MeshData* extractModelData();
};

