#pragma once

#include <glm/glm.hpp>
#include <map>
#include <string>
#include <vector>

#include "KeyFrameData.h"
#include "KeyFrame.h"
#include "JointTransformData.h"
#include "JointTransform.h"
#include "ColladaLoader.h"
#include "Animation.h"

/* This class loads up an animation collada file, gets the information from it,
 and then creates and returns an {@link Animation} from the extracted data. */
class AnimationLoader
{
	/* Creates a keyframe from the data extracted from the collada file. */
	static KeyFrame* createKeyFrame(KeyFrameData* data);

	/* Creates a joint transform from the data extracted from the collada file. */
	static JointTransform* createTransform(JointTransformData* data);

public:
	/* Loads up a collada animation file, and returns and animation created from the extracted animation data from the file. */
	static Animation* loadAnimation(const char* colladaFile);
};

