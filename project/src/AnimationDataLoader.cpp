#include "AnimationDataLoader.h"

std::vector<float> AnimationDataLoader::getKeyTimes()
{
	tinyxml2::XMLElement* timeData = animationData->FirstChildElement("animation")->FirstChildElement("source")->FirstChildElement("float_array");
	std::string text(timeData->GetText());
	std::vector<std::string> rawTimes = XMLUtils::splitText(text, " ");
	std::vector<float> times;
	for (int i = 0; i < rawTimes.size(); i++)
	{
		times.push_back(std::stof(rawTimes[i]));
	}
	return times;
}

std::vector<KeyFrameData*> AnimationDataLoader::initKeyFrames(std::vector<float> times)
{
	std::vector<KeyFrameData*> frames;
	for (int i = 0; i < times.size(); i++)
	{
		frames.push_back(new KeyFrameData(times[i]));
	}
	return frames;
}

void AnimationDataLoader::loadJointTransforms(std::vector<KeyFrameData*> frames, tinyxml2::XMLElement* jointData, std::string rootNodeId)
{
	std::string jointNameId = getJointName(jointData);
	std::string dataId = getDataId(jointData);
	tinyxml2::XMLElement* transformData = XMLUtils::firstChildElementWithAttribute(jointData, "source", "id", dataId);
	std::string text(transformData->FirstChildElement("float_array")->GetText());
	std::vector<std::string> rawData = XMLUtils::splitText(text, " ");
	processTransforms(jointNameId, rawData, frames, jointNameId == rootNodeId);
}

std::string AnimationDataLoader::getDataId(tinyxml2::XMLNode* jointData)
{
	tinyxml2::XMLElement* aux = jointData->FirstChildElement("sampler");
	tinyxml2::XMLElement* elem = XMLUtils::firstChildElementWithAttribute(aux, "input", "semantic", "OUTPUT");
	std::string res = std::string(elem->Attribute("source"));
	return res.substr(1);
}

std::string AnimationDataLoader::getJointName(tinyxml2::XMLNode* jointData)
{
	tinyxml2::XMLElement* channelNode = jointData->FirstChildElement("channel");
	std::string text(channelNode->Attribute("target"));
	size_t pos = 0;
	std::string res;
	if ((pos = text.find("/")) != std::string::npos)
	{
		res = text.substr(0, pos).c_str();
	}
	return res;
}

void AnimationDataLoader::processTransforms(std::string jointName, std::vector<std::string> rawData, std::vector<KeyFrameData*> keyFrames, bool root)
{
	float* matrixData = new float[16];
	int auxIndex;

	for (int i = 0; i < keyFrames.size(); i++)
	{
		for (int j = 0; j < 16; j++)
		{
			auxIndex = i * 16 + j;
			matrixData[j] = std::stof(rawData[auxIndex]);
		}
		glm::mat4 transform;
		for (int i = 3; i >= 0; i--)
		{
			for (int j = 3; j >= 0; j--)
			{
				auxIndex = i * 4 + j;
				transform[i][j] = matrixData[auxIndex];
			}
		}
		transform = glm::transpose(transform);
		if (root)
		{
			//because up axis in Blender is different to up axis in game
			transform *= CORRECTION;
		}
		keyFrames[i]->addJointTransform(new JointTransformData(jointName, transform));
	}
}

std::string AnimationDataLoader::findRootJointName()
{
	tinyxml2::XMLElement* aux = jointHierarchy->FirstChildElement("visual_scene");
	tinyxml2::XMLElement* skeleton = XMLUtils::firstChildElementWithAttribute(aux, "node", "id", "Armature");
	return skeleton->FirstChildElement("node")->Attribute("id");
}

AnimationDataLoader::AnimationDataLoader(tinyxml2::XMLElement* animationData, tinyxml2::XMLElement* jointHierarchy)
{
	this->animationData = animationData;
	this->jointHierarchy = jointHierarchy;
}

AnimationData* AnimationDataLoader::extractAnimation()
{
	std::string rootNode = findRootJointName();
	std::vector<float> times = getKeyTimes();
	float duration = times[times.size() - 1];
	std::vector<KeyFrameData*> keyFrames = initKeyFrames(times);
	std::vector<tinyxml2::XMLElement*> animationNodes = XMLUtils::childrenWithName(animationData, "animation");

	for (tinyxml2::XMLElement* jointNode : animationNodes)
	{
		loadJointTransforms(keyFrames, jointNode, rootNode);
	}

	return new AnimationData(duration, keyFrames);
}