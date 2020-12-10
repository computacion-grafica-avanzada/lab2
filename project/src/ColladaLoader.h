#pragma once

#include <tinyxml2.h>

#include "AnimatedModelData.h"
#include "AnimationData.h"
#include "MeshData.h"
#include "SkeletonData.h"
#include "SkinningData.h"
#include "AnimationDataLoader.h"
#include "GeometryLoader.h"
#include "SkeletonLoader.h"
#include "SkinLoader.h"

class ColladaLoader
{
public:
	static AnimatedModelData* loadColladaModel(const char* colladaFile, int maxWeights);
	static AnimationData* loadColladaAnimation(const char* colladaFile);
};

