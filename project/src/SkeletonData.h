#pragma once

#include "JointData.h"

class SkeletonData
{
public:
	int jointCount;
	JointData* headJoint;
	SkeletonData(int jointCount, JointData* headJoint);
};

