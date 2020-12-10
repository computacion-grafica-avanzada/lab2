#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm\glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>

class Transform
{
private:
	glm::vec3 pos;
	glm::quat rot;
	glm::vec3 scale;

public:
	Transform(const glm::vec3& pos = glm::vec3(),
		const glm::vec3& rot = glm::vec3(),
		const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = glm::quat(rot);
		this->scale = scale;
	}

	inline glm::mat4 getModel() const
	{
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 rotMat = glm::toMat4(rot);
		glm::mat4 scaleMat = glm::scale(scale);

		return posMat * rotMat * scaleMat;
	}

	inline glm::vec3& getPos()
	{
		return pos;
	}

	inline glm::quat& getRot()
	{
		return rot;
	}

	inline glm::vec3& getScale()
	{
		return scale;
	}

	inline void SetPos(const glm::vec3& pos)
	{
		this->pos = pos;
	}

	inline void SetRot(const glm::quat& rot)
	{
		this->rot = rot;
	}

	inline void SetScale(const glm::vec3& scale)
	{
		this->scale = scale;
	}
};

#endif