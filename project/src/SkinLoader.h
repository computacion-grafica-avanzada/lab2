#pragma once

#include <tinyxml2.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexSkinData.h"
#include "XMLUtils.h"
#include "SkinningData.h"

class SkinLoader
{
	const glm::mat4 CORRECTION = glm::rotate(glm::identity<glm::mat4>(), glm::radians(-90.0f), glm::vec3(1, 0, 0));

	tinyxml2::XMLElement* skinningData;
	int maxWeights;

	std::vector<std::string> loadJointsList();
	std::vector<float> loadWeights();
	std::vector<glm::mat4> SkinLoader::loadInverseBindTransforms();
	std::vector<int> getEffectiveJointsCounts(tinyxml2::XMLElement* weightsDataNode);
	std::vector<VertexSkinData*> getSkinData(tinyxml2::XMLElement* weightsDataNode, std::vector<int> counts, std::vector<float> weights);

public:
	SkinLoader(tinyxml2::XMLElement* controllersNode, int maxWeights);
	SkinningData* extractSkinData();
};

