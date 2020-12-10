#include "SkeletonLoader.h"

JointData* SkeletonLoader::loadJointData(tinyxml2::XMLElement* jointNode, bool isRoot)
{
	JointData* joint = extractMainJointData(jointNode, isRoot);
	std::vector<tinyxml2::XMLElement*> children = XMLUtils::childrenWithName(jointNode, "node");
	for (tinyxml2::XMLElement* childNode : children)
	{
		joint->addChild(loadJointData(childNode, false));
	}
	return joint;
}

JointData* SkeletonLoader::extractMainJointData(tinyxml2::XMLElement* jointNode, bool isRoot)
{
	std::string nameId(jointNode->Attribute("id"));
	auto it = std::find(boneOrder.begin(), boneOrder.end(), nameId);
	int index = -1;
	// If element was found
	if (it != boneOrder.end())
	{
		int index = it - boneOrder.begin();
	}
	std::vector<std::string> matrixData = XMLUtils::splitText(jointNode->FirstChildElement("matrix")->GetText(), " ");
	glm::mat4 matrix = glm::identity<glm::mat4>();
	matrix = convertData(matrixData);
	matrix = glm::transpose(matrix);
	if (isRoot)
	{
		//because in Blender z is up, but in our game y is up.
		matrix *= CORRECTION;
	}
	jointCount++;
	return new JointData(index, nameId, matrix);
}

glm::mat4 SkeletonLoader::convertData(std::vector<std::string> rawData)
{
	std::vector<float> matrixData;
	glm::mat4 matrix;
	int auxIndex;
	for (int i = 0; i < 16; i++)
	{
		matrixData[i] = std::stof(rawData[i]);
	}
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 3; i >= 0; j--)
		{
			auxIndex = i * 4 + j;
			matrix[i][j] = matrixData[auxIndex];
		}
	}
	return matrix;
}

SkeletonLoader::SkeletonLoader(tinyxml2::XMLElement* visualSceneNode, std::vector<std::string> boneOrder)
{
	armatureData = XMLUtils::firstChildElementWithAttribute(visualSceneNode->FirstChildElement("visual_scene"), "node", "id", "Armature");
	boneOrder = boneOrder;
}

SkeletonData* SkeletonLoader::extractBoneData()
{
	tinyxml2::XMLElement* headNode = armatureData->FirstChildElement("node");
	JointData* headJoint = loadJointData(headNode, true);
	return new SkeletonData(jointCount, headJoint);
}