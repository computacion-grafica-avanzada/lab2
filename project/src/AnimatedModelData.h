#pragma once

#include "MeshData.h"
#include "SkeletonData.h"

// Contains the extracted data for an animated model, which includes the mesh data, and skeleton (joints heirarchy) data.
class AnimatedModelData
{
	MeshData* mesh;
	SkeletonData* joints;

public:
	AnimatedModelData(MeshData* mesh, SkeletonData* joints);
	MeshData* getMeshData();
	SkeletonData* getJointsData();
};

