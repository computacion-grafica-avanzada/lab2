#pragma once

#include <vector>

#include "KeyFrame.h"

class Animation
{
	float length;//in seconds
	std::vector<KeyFrame*> keyFrames;

public:
	/**
	 * @param lengthInSeconds
	 *            - the total length of the animation in seconds.
	 * @param frames
	 *            - all the keyframes for the animation, ordered by time of
	 *            appearance in the animation.
	 */
	Animation(float lengthInSeconds, std::vector<KeyFrame*> frames);

	/**
	 * @return The length of the animation in seconds.
	 */
	float getLength();

	/**
	 * @return An array of the animation's keyframes. The array is ordered based
	 *         on the order of the keyframes in the animation (first keyframe of
	 *         the animation in array position 0).
	 */
	std::vector<KeyFrame*> getKeyFrames();
};