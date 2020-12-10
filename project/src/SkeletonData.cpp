#include "SkeletonData.h"

SkeletonData::SkeletonData(int jointCount, JointData* headJoint) {
	this->jointCount = jointCount;
	this->headJoint = headJoint;
}