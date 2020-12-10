#pragma once

#include <vector>
#include <algorithm>

class VertexSkinData
{
	void fillEmptyWeights(int max);
	float saveTopWeights(std::vector<float> topWeightsArray);
	void refillWeightList(std::vector<float> topWeights, float total);
	void removeExcessJointIds(int max);

public:
	std::vector<int> jointIds;
	std::vector<float> weights;

	void addJointEffect(int jointId, float weight);
	void limitJointNumber(int max);
};

