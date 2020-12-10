#ifndef ANIMATION_SHADER_H
#define ANIMATION_SHADER_H

#include <string>
#include <GL\glew.h>
#include <vector>
#include <glm\glm.hpp>
#include "Transform.h"
#include "Camera.h"
#include "Shader.h"

static const unsigned int MAX_JOINTS = 50;

class AnimationShader : public Shader
{
private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,
		VIEW_PROJECTION_U,
		JOINT_TRANSFORMS_U,

		NUM_UNIFORMS
	};

public:
	AnimationShader(const char* vertexFile, const char* fragmentFile);
	virtual ~AnimationShader();

	void update(const Transform& transform, const Camera& camera, std::vector<glm::mat4> jointVector);
	void bind();
};

#endif