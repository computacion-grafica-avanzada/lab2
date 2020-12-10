#include "AnimationData.h"

AnimationData::AnimationData(float lengthSeconds, std::vector<KeyFrameData*> keyFrames)
{
	this->lengthSeconds = lengthSeconds;
	this->keyFrames = keyFrames;
}
