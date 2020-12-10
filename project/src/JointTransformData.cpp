#include "JointTransformData.h"

JointTransformData::JointTransformData(std::string jointNameId, glm::mat4 jointLocalTransform) {
	this->jointNameId = jointNameId;
	this->jointLocalTransform = jointLocalTransform;
}
