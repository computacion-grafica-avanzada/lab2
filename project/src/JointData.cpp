#include "JointData.h"

JointData::JointData(int index, std::string nameId, glm::mat4 bindLocalTransform) {
	this->index = index;
	this->nameId = nameId;
	this->bindLocalTransform = bindLocalTransform;
}

void JointData::addChild(JointData* child) {
	children.push_back(child);
}
