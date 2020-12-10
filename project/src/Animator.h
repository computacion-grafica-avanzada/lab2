#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <memory>
#include <unordered_map>
#include "Animation.h"
class Model;
class Joint;

class Animator
{
private:
	Model* model;
	std::vector<std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> currentAnimation;
	double animationTime;

	std::unordered_map<std::string, glm::mat4> calculateJointTransforms();

	glm::vec3 getInterpolatedPos(std::pair<double, glm::vec3> start, std::pair<double, glm::vec3> end);
	glm::quat getInterpolatedRot(std::pair<double, glm::quat> start, std::pair<double, glm::quat> end);
	glm::vec3 getInterpolatedScale(std::pair<double, glm::vec3> start, std::pair<double, glm::vec3> end);
	glm::quat slerp(glm::quat v0, glm::quat v1, float t);

public:
	Animator(Model* model);

	void startAnimation(const std::string& animationName);
	void addAnimation(const json& jsonAnimation);
	void update(double elapsedTime);
};

#endif