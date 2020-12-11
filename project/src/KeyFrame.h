#pragma once

#include <string>
#include <map>

#include "JointTransform.h"

class KeyFrame
{
	float timeStamp;
	std::map<std::string, JointTransform*> pose;


public:

	/**
	 * @return The desired bone-space transforms of all the joints at this
	 *         keyframe, of the animation, indexed by the name of the joint that
	 *         they correspond to. This basically represents the "pose" at this
	 *         keyframe.
	 */
	std::map<std::string, JointTransform*> getJointKeyFrames();

	/**
	 * @return The time in seconds of the keyframe in the animation.
	 */
	float getTimeStamp();


	/**
	 * @param timeStamp
	 *            - the time (in seconds) that this keyframe occurs during the
	 *            animation.
	 * @param jointKeyFrames
	 *            - the local-space transforms for all the joints at this
	 *            keyframe, indexed by the name of the joint that they should be
	 *            applied to.
	 */
	KeyFrame(float timeStamp, std::map<std::string, JointTransform*> jointKeyFrames);
};

