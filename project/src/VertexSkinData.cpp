#include "VertexSkinData.h"

void VertexSkinData::fillEmptyWeights(int max) {
	while (jointIds.size() < max) {
		jointIds.push_back(0);
		weights.push_back(0);
	}
}

float VertexSkinData::saveTopWeights(std::vector<float> topWeightsArray) {
	float total = 0;
	for (int i = 0; i < topWeightsArray.size(); i++) {
		topWeightsArray[i] = weights[i];
		total += topWeightsArray[i];
	}
	return total;
}

void VertexSkinData::refillWeightList(std::vector<float> topWeights, float total) {
	weights.clear();
	for (int i = 0; i < topWeights.size(); i++) {
		weights.push_back(std::min(topWeights[i] / total, 1.0f));
	}
}

void VertexSkinData::removeExcessJointIds(int max) {
	while (jointIds.size() > max) {
		jointIds.erase(jointIds.begin() + (jointIds.size() - 1));
	}
}

void VertexSkinData::addJointEffect(int jointId, float weight) {
	for (int i = 0; i < weights.size(); i++) {
		if (weight > weights[i]) {
			jointIds[i] = jointId;
			weights[i] = weight;
			return;
		}
	}
	jointIds.push_back(jointId);
	weights.push_back(weight);
}

void VertexSkinData::limitJointNumber(int max) {
	if (jointIds.size() > max) {
		std::vector<float> topWeights;
		float total = saveTopWeights(topWeights);
		refillWeightList(topWeights, total);
		removeExcessJointIds(max);
	}
	else if (jointIds.size() < max) {
		fillEmptyWeights(max);
	}
}