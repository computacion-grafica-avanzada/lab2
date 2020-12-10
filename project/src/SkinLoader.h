#pragma once

#include <tinyxml2.h>
#include <vector>
#include <string>

#include "VertexSkinData.h"
#include "XMLUtils.h"
#include "SkinningData.h"

class SkinLoader
{
	tinyxml2::XMLElement* skinningData;
	int maxWeights;

	std::vector<std::string> loadJointsList();
	std::vector<float> loadWeights();
	std::vector<int> getEffectiveJointsCounts(tinyxml2::XMLElement* weightsDataNode);
	std::vector<VertexSkinData*> getSkinData(tinyxml2::XMLElement* weightsDataNode, std::vector<int> counts, std::vector<float> weights);

public:
	SkinLoader(tinyxml2::XMLElement* controllersNode, int maxWeights);
	SkinningData* extractSkinData();
};

