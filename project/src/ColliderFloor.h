#pragma once
#include <glm/glm.hpp>
#include "Mesh.h"
#include <set>
#include "octree/octree.h"

using namespace std;

class ColliderFloor
{
private:
	std::set<Mesh*> meshes;
	//Octree<glm::vec3> octree;
public:
	ColliderFloor(std::set<Mesh*> meshes);

	static bool isPointInTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 pos);
	static float heightOfTriangleAtPos(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 pos);
	float getHeightAtPos(glm::vec3 pos);
};

