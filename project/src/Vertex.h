#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "VertexSkinData.h"

class Vertex
{
	const int NO_INDEX = -1;

	glm::vec3 position;
	int textureIndex = NO_INDEX;
	int normalIndex = NO_INDEX;
	Vertex* duplicateVertex;
	int index;
	float length;
	std::vector<glm::vec3> tangents;
	glm::vec3 averagedTangent;
	VertexSkinData* weightsData;

public:
	Vertex(int index, glm::vec3 position, VertexSkinData* weightsData);
	void addTangent(glm::vec3 tangent);
	void averageTangents();
	bool isSet();
	bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
	glm::vec3 getPosition();
	void setTextureIndex(int textureIndex);
	int getTextureIndex();
	void setNormalIndex(int normalIndex);
	int getNormalIndex();
	void setDuplicateVertex(Vertex* duplicateVertex);
	Vertex* getDuplicateVertex();
	int getIndex();
	float getLength();
	glm::vec3 getAverageTangent();
	VertexSkinData* getWeightsData();
};

