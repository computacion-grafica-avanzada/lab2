#pragma once

#include <glm/mat4x4.hpp>
#include <vector>
#include <string>

/* Contains the extracted data for a single joint in the model. This stores the
joint's index, name, and local bind transform. */
class JointData
{
public:
	int index;
	std::string nameId;
	glm::mat4 bindLocalTransform;
	std::vector<JointData*> children;

	JointData(int index, std::string nameId, glm::mat4 bindLocalTransform);
	void addChild(JointData* child);
};

