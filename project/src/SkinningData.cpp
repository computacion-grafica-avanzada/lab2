#include "SkinningData.h"

SkinningData::SkinningData(std::vector<std::string> jointOrder, std::vector<VertexSkinData*> verticesSkinData, std::vector<glm::mat4> inverseBindTransforms) {
	this->jointOrder = jointOrder;
	this->verticesSkinData = verticesSkinData;
	this->inverseBindTransforms = inverseBindTransforms;
}