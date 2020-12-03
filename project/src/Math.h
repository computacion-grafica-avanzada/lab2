#pragma once
#include <glm/glm.hpp>
#include <algorithm>

static class Math
{
public:
	static float distSquared(glm::vec3 v1, glm::vec3 v2);
	static bool checkRangesIntersection(float min1, float max1, float min2, float max2);
};

