#include "SkinLoader.h"

std::vector<std::string> SkinLoader::loadJointsList()
{
	tinyxml2::XMLElement* inputNode = skinningData->FirstChildElement("vertex_weights");
	std::string aux = std::string(XMLUtils::firstChildElementWithAttribute(inputNode, "input", "semantic", "JOINT")->Attribute("source"));
	std::string jointDataId = aux.substr(1);
	tinyxml2::XMLElement* jointsNode = XMLUtils::firstChildElementWithAttribute(skinningData, "source", "id", jointDataId)->FirstChildElement("Name_array");
	std::vector<std::string> names = XMLUtils::splitText(jointsNode->GetText(), " ");
	std::vector<std::string> jointsList;
	for (std::string name : names)
	{
		jointsList.push_back(name);
	}
	return jointsList;
}

std::vector<float> SkinLoader::loadWeights()
{
	tinyxml2::XMLElement* inputNode = skinningData->FirstChildElement("vertex_weights");
	std::string aux = std::string(XMLUtils::firstChildElementWithAttribute(inputNode, "input", "semantic", "WEIGHT")->Attribute("source"));
	std::string weightsDataId = aux.substr(1);
	tinyxml2::XMLElement* weightsNode = XMLUtils::firstChildElementWithAttribute(skinningData, "source", "id", weightsDataId)->FirstChildElement("float_array");
	std::vector<std::string> rawData = XMLUtils::splitText(weightsNode->GetText(), " ");
	std::vector<float> weights;
	for (int i = 0; i < rawData.size(); i++)
	{
		weights.push_back(std::stof(rawData[i]));
	}
	return weights;
}

std::vector<int> SkinLoader::getEffectiveJointsCounts(tinyxml2::XMLElement* weightsDataNode)
{
	std::vector<std::string> rawData = XMLUtils::splitText(weightsDataNode->FirstChildElement("vcount")->GetText(), " ");
	std::vector<int> counts;
	for (int i = 0; i < rawData.size(); i++)
	{
		counts.push_back(std::stoi(rawData[i]));
	}
	return counts;
}

std::vector<VertexSkinData*> SkinLoader::getSkinData(tinyxml2::XMLElement* weightsDataNode, std::vector<int> counts, std::vector<float> weights)
{
	std::vector<std::string> rawData = XMLUtils::splitText(weightsDataNode->FirstChildElement("v")->GetText(), " ");
	std::vector<VertexSkinData*> skinningData;
	int pointer = 0;
	std::string aux;
	int jointId, weightId;
	for (int count : counts)
	{
		VertexSkinData* skinData = new VertexSkinData();
		for (int i = 0; i < count; i++)
		{
			aux = rawData[pointer++];
			jointId = std::stoi(aux);
			aux = rawData[pointer++];
			weightId = std::stoi(aux);
			if (weightId < weights.size())
			{
			skinData->addJointEffect(jointId, weights[weightId]);
			}
		}
		skinData->limitJointNumber(maxWeights);
		skinningData.push_back(skinData);
	}
	return skinningData;
}

SkinLoader::SkinLoader(tinyxml2::XMLElement* controllersNode, int maxWeights)
{
	tinyxml2::XMLElement* aux = controllersNode->FirstChildElement("controller");
	this->skinningData = aux->FirstChildElement("skin");
	this->maxWeights = maxWeights;
}

SkinningData* SkinLoader::extractSkinData()
{
	std::vector<std::string> jointsList = loadJointsList();
	std::vector<float> weights = loadWeights();
	tinyxml2::XMLElement* weightsDataNode = skinningData->FirstChildElement("vertex_weights");
	std::vector<int> effectorJointCounts = getEffectiveJointsCounts(weightsDataNode);
	std::vector<VertexSkinData*> vertexWeights = getSkinData(weightsDataNode, effectorJointCounts, weights);
	return new SkinningData(jointsList, vertexWeights);
}