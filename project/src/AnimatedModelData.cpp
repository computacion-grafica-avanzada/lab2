#include "AnimatedModelData.h"

AnimatedModelData::AnimatedModelData(MeshData* mesh, SkeletonData* joints)
{
	this->mesh = mesh;
	this->joints = joints;
}

MeshData* AnimatedModelData::getMeshData()
{
	return mesh;
}

SkeletonData* AnimatedModelData::getJointsData()
{
	return joints;
}
