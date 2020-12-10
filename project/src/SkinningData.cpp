#include "SkinningData.h"

SkinningData::SkinningData(std::vector<std::string> jointOrder, std::vector<VertexSkinData*> verticesSkinData) {
	this->jointOrder = jointOrder;
	this->verticesSkinData = verticesSkinData;
}