#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "VertexSkinData.h"

class SkinningData
{
public:
	std::vector<std::string> jointOrder;
	std::vector<VertexSkinData*> verticesSkinData;
	std::vector<glm::mat4> inverseBindTransforms;

	SkinningData(std::vector<std::string> jointOrder, std::vector<VertexSkinData*> verticesSkinData, std::vector<glm::mat4> inverseBindTransforms);
};

