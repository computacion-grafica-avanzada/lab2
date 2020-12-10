#pragma once

#include <vector>
#include "JointTransformData.h"

class KeyFrameData
{
public:
	float time;
	std::vector<JointTransformData*> jointTransforms;
	KeyFrameData(float time);
	void addJointTransform(JointTransformData* transform);
};

