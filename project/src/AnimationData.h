#pragma once

#include <vector>

#include "KeyFrameData.h"

/* Contains the extracted data for an animation, which includes the length
of the entire animationand the data for all the keyframes of the animation.*/
class AnimationData
{
public:
	float lengthSeconds;
	std::vector<KeyFrameData*> keyFrames;

	AnimationData(float lengthSeconds, std::vector<KeyFrameData*> keyFrames);
};

