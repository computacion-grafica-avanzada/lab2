#include "AnimationLoader.h"

/* Creates a keyframe from the data extracted from the collada file. */
KeyFrame* AnimationLoader::createKeyFrame(KeyFrameData* data) {
	std::map<std::string, JointTransform*> map;
	for (JointTransformData* jointData : data->jointTransforms) {
		JointTransform* jointTransform = createTransform(jointData);
		map.insert({ jointData->jointNameId, jointTransform });
	}
	return new KeyFrame(data->time, map);
}

/* Creates a joint transform from the data extracted from the collada file. */
JointTransform* AnimationLoader::createTransform(JointTransformData* data) {
	glm::mat4 mat = data->jointLocalTransform;
	glm::vec3 translation(mat[3]);
	glm::quat rotation = glm::quat_cast(mat);
	return new JointTransform(translation, rotation);
}

/* Loads up a collada animation file, and returns and animation created from the extracted animation data from the file. */
Animation* AnimationLoader::loadAnimation(const char* colladaFile) {
	AnimationData* animationData = ColladaLoader::loadColladaAnimation(colladaFile);
	std::vector<KeyFrame*> frames;
	for (int i = 0; i < animationData->keyFrames.size(); i++) {
		frames.push_back(createKeyFrame(animationData->keyFrames[i]));
	}
	return new Animation(animationData->lengthSeconds, frames);
}