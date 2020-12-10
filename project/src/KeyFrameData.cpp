#include "KeyFrameData.h"

KeyFrameData::KeyFrameData(float time) {
	this->time = time;
}

void KeyFrameData::addJointTransform(JointTransformData* transform) {
	jointTransforms.push_back(transform);
}