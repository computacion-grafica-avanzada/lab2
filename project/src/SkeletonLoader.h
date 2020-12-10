#pragma once

#include <tinyxml2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

#include "JointData.h"
#include "SkeletonData.h"
#include "XMLUtils.h"

class SkeletonLoader
{
	const glm::mat4 CORRECTION = glm::rotate(glm::identity<glm::mat4>(), glm::radians(-90.0f), glm::vec3(1, 0, 0));

	tinyxml2::XMLElement* armatureData;
	std::vector<std::string> boneOrder;
	int jointCount = 0;

	JointData* loadJointData(tinyxml2::XMLElement* jointNode, bool isRoot);
	JointData* extractMainJointData(tinyxml2::XMLElement* jointNode, bool isRoot);
	glm::mat4 convertData(std::vector<std::string> rawData);

public:
	SkeletonLoader(tinyxml2::XMLElement* visualSceneNode, std::vector<std::string> boneOrder);
	SkeletonData* extractBoneData();
};

