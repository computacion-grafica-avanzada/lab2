#pragma once

#include <glm/mat4x4.hpp>
#include <vector>
#include <string>

/* Contains the extracted data for a single joint in the model. This stores the
joint's index, name, and local bind transform. */
class JointTransformData
{
public:
	std::string jointNameId;
	glm::mat4 jointLocalTransform;

	JointTransformData(std::string jointNameId, glm::mat4 jointLocalTransform);
};

