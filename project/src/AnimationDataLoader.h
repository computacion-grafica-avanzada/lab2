#pragma once

#include <tinyxml2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

#include "KeyFrameData.h"
#include "AnimationData.h"
#include "JointTransformData.h"
#include "XMLUtils.h"

class AnimationDataLoader
{
	const glm::mat4 CORRECTION = glm::rotate(glm::identity<glm::mat4>(), glm::radians(-90.0f), glm::vec3(1, 0, 0));

	tinyxml2::XMLElement* animationData;
	tinyxml2::XMLElement* jointHierarchy;

	std::vector<float> getKeyTimes();
	std::vector<KeyFrameData*> initKeyFrames(std::vector<float> times);
	void loadJointTransforms(std::vector<KeyFrameData*> frames, tinyxml2::XMLNode* jointData, std::string rootNodeId);
	std::string getDataId(tinyxml2::XMLNode* jointData);
	std::string getJointName(tinyxml2::XMLNode* jointData);
	void processTransforms(std::string jointName, std::vector<std::string> rawData, std::vector<KeyFrameData*> keyFrames, bool root);
	std::string findRootJointName();

public:
	AnimationDataLoader(tinyxml2::XMLElement* animationData, tinyxml2::XMLElement* jointHierarchy);
	AnimationData* extractAnimation();
};

