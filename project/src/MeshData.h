#pragma once

#include <vector>

/* This object contains all the mesh data for an animated model that is to be loaded into the VAO. */
class MeshData
{
public:
	const int DIMENSIONS = 3;

	float* vertices;
	float* textureCoords;
	float* normals;
	int* indices;
	int* jointIds;
	float* vertexWeights;
	int vertexCount;

	MeshData(float* vertices, float* textureCoords, float* normals, int* indices, int* jointIds, float* vertexWeights, int verticesCount);
};

