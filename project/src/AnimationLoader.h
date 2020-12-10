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
	static KeyFrame* createKeyFrame(KeyFrameData* data) {
		std::map<std::string, JointTransform*> map;
		for (JointTransformData* jointData : data->jointTransforms) {
			JointTransform* jointTransform = createTransform(jointData);
			map.insert({ jointData->jointNameId, jointTransform });
		}
		return new KeyFrame(data->time, map);
	}

	/* Creates a joint transform from the data extracted from the collada file. */
	static JointTransform* createTransform(JointTransformData* data) {
		glm::mat4 mat = data->jointLocalTransform;
		glm::vec3 translation(mat[3]);
		Quaternion rotation = Quaternion.fromMatrix(mat);
		return new JointTransform(translation, rotation);
	}

public:
	/* Loads up a collada animation file, and returns and animation created from the extracted animation data from the file. */
	static Animation loadAnimation(const char* colladaFile) {
		AnimationData* animationData = ColladaLoader::loadColladaAnimation(colladaFile);
		std::vector<KeyFrame*> frames;
		for (int i = 0; i < animationData->keyFrames.size(); i++) {
			frames.push_back(createKeyFrame(animationData->keyFrames[i]));
		}
		return new Animation(animationData->lengthSeconds, frames);
	}
};

