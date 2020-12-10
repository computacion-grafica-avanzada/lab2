#include "Animator.h"
#include "..\AnimatedModel\Model.h"
#include <iostream>

Animator::Animator(Model* model)
{
	model = model;
}

void Animator::startAnimation(const std::string& animationName)
{
	for (auto animation : animations)
	{
		if (animation->getName() == animationName)
		{
			animationTime = 0;
			currentAnimation = animation;
		}
	}
}

void Animator::addAnimation(const json& jsonAnimation)
{
	animations.push_back(std::make_shared<Animation>(jsonAnimation));
}

void Animator::update(double elapsedTime)
{
	if (currentAnimation == nullptr) {
		return;
	}
	animationTime += elapsedTime;
	if (animationTime > currentAnimation->getDuration()) animationTime -= currentAnimation->getDuration();

	std::unordered_map<std::string, glm::mat4> jointMap = calculateJointTransforms();

	for (auto jointTransform : jointMap)
	{
		std::shared_ptr<Joint> joint = model->FindJoint(jointTransform.first);
		if (joint != nullptr) joint->setTransform(jointTransform.second);
	}
	model->InitJointHierarchy(model->getRootJoint(), glm::scale(glm::vec3(1)));
}

std::unordered_map<std::string, glm::mat4> Animator::calculateJointTransforms()
{
	std::unordered_map<std::string, glm::mat4> jointTransforms;
	for (auto jointKeys : currentAnimation->getJointAnims())
	{
		//Using upper bound as it will never return the first value of a map.
		auto posNext = jointKeys._positionKeys.upper_bound(animationTime);
		auto rotNext = jointKeys._rotationKeys.upper_bound(animationTime);
		auto scaleNext = jointKeys._scallingKeys.upper_bound(animationTime);

		if (posNext == jointKeys._positionKeys.end()) posNext--;
		if (rotNext == jointKeys._rotationKeys.end()) rotNext--;
		if (scaleNext == jointKeys._scallingKeys.end()) scaleNext--;

		glm::vec3 pos = getInterpolatedPos(*(std::prev(posNext)), *posNext);
		glm::quat rot = getInterpolatedRot(*(std::prev(rotNext)), *rotNext);
		glm::vec3 scale = getInterpolatedScale(*(std::prev(scaleNext)), *scaleNext);

		glm::mat4 transform = glm::translate(pos) * glm::toMat4(rot) * glm::scale(scale);

		jointTransforms.insert(std::make_pair(jointKeys._name, transform));
	}
	return jointTransforms;
}

glm::vec3 Animator::getInterpolatedPos(std::pair<double, glm::vec3> start, std::pair<double, glm::vec3> end)
{
	double delta = end.first - start.first;
	double factor = (animationTime - start.first) / delta;
	glm::vec3 deltaPos = end.second - start.second;
	glm::vec3 pos = start.second + (float)factor * deltaPos;
	return pos;
}

glm::quat Animator::getInterpolatedRot(std::pair<double, glm::quat> start, std::pair<double, glm::quat> end)
{
	double delta = end.first - start.first;
	double factor = (animationTime - start.first) / delta;
	glm::quat rot = slerp(start.second, end.second, (float)factor);
	return glm::normalize(rot);
}

//Adapted from wikipedia: https://en.wikipedia.org/wiki/Slerp#Source_code
glm::quat Animator::slerp(glm::quat v0, glm::quat v1, float t) {
	// Only unit quaternions are valid rotations.
	// Normalize to avoid undefined behavior.
	v0 = glm::normalize(v0);
	v1 = glm::normalize(v1);

	// Compute the cosine of the angle between the two vectors.
	float dot = glm::dot(v0, v1);

	// If the dot product is negative, the quaternions
	// have opposite handed-ness and slerp won't take
	// the shorter path. Fix by reversing one quaternion.
	if (dot < 0.0f) {
		v1 = -v1;
		dot = -dot;
	}

	//const double DOT_THRESHOLD = 0.9995;
	//if (dot > DOT_THRESHOLD) {
	//	// If the inputs are too close for comfort, linearly interpolate
	//	// and normalize the result.

	//	glm::quat result = v0 + t * (v1 – v0);
	//	result = glm::normalize(result);
	//	return result;
	//}

	glm::clamp(dot, -1.0f, 1.0f);           // Robustness: Stay within domain of acos()
	float theta_0 = acos(dot);  // theta_0 = angle between input vectors
	float theta = theta_0 * t;    // theta = angle between v0 and result

	float s0 = cos(theta) - dot * sin(theta) / sin(theta_0);  // == sin(theta_0 - theta) / sin(theta_0)
	float s1 = sin(theta) / sin(theta_0);

	return (s0 * v0) + (s1 * v1);
}

glm::vec3 Animator::getInterpolatedScale(std::pair<double, glm::vec3> start, std::pair<double, glm::vec3> end)
{
	double delta = end.first - start.first;
	double factor = (animationTime - start.first) / delta;
	glm::vec3 deltaScale = end.second - start.second;
	glm::vec3 scale = start.second + (float)factor * deltaScale;
	return scale;
}
