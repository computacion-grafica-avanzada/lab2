#pragma once

#include <vector>
#include <string>

#include "VertexSkinData.h"

class SkinningData
{
public:
	std::vector<std::string> jointOrder;
	std::vector<VertexSkinData*> verticesSkinData;

	SkinningData(std::vector<std::string> jointOrder, std::vector<VertexSkinData*> verticesSkinData);
};

