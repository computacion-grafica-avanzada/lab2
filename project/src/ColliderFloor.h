#pragma once
#include <glm/glm.hpp>
#include "Mesh.h"

class ColliderFloor
{
private:
	Mesh* mesh;
public:
	ColliderFloor(Mesh* mesh);

	static bool isPointInTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 pos);
	static float heightOfTriangleAtPos(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 pos);
	float getHeightAtPos(glm::vec3 pos);
};

