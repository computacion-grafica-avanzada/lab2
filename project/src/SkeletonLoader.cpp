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
		index = it - boneOrder.begin();
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
	return new JointData(index, nameId, matrix, inverseBindTransforms[index]);
}

glm::mat4 SkeletonLoader::convertData(std::vector<std::string> rawData)
{
	return XMLUtils::rawDataToMat4(rawData);
	//glm::mat4 matrix = XMLUtils::rawDataToMat4(rawData);
	//int auxIndex = 0;
	//std::string aux;
	////float matrixData[16];
	////for (int i = rawData.size() - 1; i >= 0; i--)
	////{
	////	aux = rawData[i];
	////	matrixData[i] = std::stof(aux);
	////}
	////matrix = glm::make_mat4(matrixData);

	//std::vector<float> matrixData;
	//for (int i = 0; i < rawData.size(); i++)
	//{
	//	aux = rawData[i];
	//	//aux = rawData[rawData.size() - i - 1];

	//	matrixData.push_back(std::stof(aux));
	//}
	//for (int col = 0; col < 4; col++)
	//{
	//	for (int row = 0; row < 4; row++)
	//	{
	//		auxIndex = col * 4 + row;
	//		matrix[col][row] = matrixData[auxIndex];
	//	}
	//}
	//return matrix;
}

SkeletonLoader::SkeletonLoader(tinyxml2::XMLElement* visualSceneNode, std::vector<std::string> boneOrder, std::vector<glm::mat4> inverseBindTransforms)
{
	armatureData = XMLUtils::firstChildElementWithAttribute(visualSceneNode->FirstChildElement("visual_scene"), "node", "id", "Armature");
	this->boneOrder = boneOrder;
	this->inverseBindTransforms = inverseBindTransforms;
}

SkeletonData* SkeletonLoader::extractBoneData()
{
	tinyxml2::XMLElement* headNode = armatureData->FirstChildElement("node");
	JointData* headJoint = loadJointData(headNode, true);
	return new SkeletonData(jointCount, headJoint);
}