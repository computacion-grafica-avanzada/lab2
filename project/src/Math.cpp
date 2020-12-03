#include "Math.h"

float Math::distSquared(glm::vec3 v1, glm::vec3 v2)
{
	return (v1.x - v2.x) * (v1.x - v2.x) +
		(v1.y - v2.y) * (v1.y - v2.y) +
		(v1.z - v2.z) * (v1.z - v2.z);
}

bool Math::checkRangesIntersection(float min1, float max1, float min2, float max2)
{
	float maxMin = std::max(min1, min2);
	float minMax = std::min(max1, max2);
	return maxMin < minMax;
}

