#include "JointData.h"

JointData::JointData(int index, std::string nameId, glm::mat4 bindLocalTransform, glm::mat4 inverseBindTransform) {
	this->index = index;
	this->nameId = nameId;
	this->bindLocalTransform = bindLocalTransform;
	this->inverseBindTransform = inverseBindTransform;
}

void JointData::addChild(JointData* child) {
	children.push_back(child);
}
