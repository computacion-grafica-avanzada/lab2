#include "AnimatedModelData.h"

AnimatedModelData::AnimatedModelData(MeshData* mesh, SkeletonData* joints)
{
	this->joints = joints;
	this->mesh = mesh;
}

MeshData* AnimatedModelData::getMeshData()
{
	return mesh;
}

SkeletonData* AnimatedModelData::getJointsData()
{
	return joints;
}
