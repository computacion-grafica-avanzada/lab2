#include "AnimationShader.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>

AnimationShader::AnimationShader(const char* vertexFile, const char* fragmentFile) :
	Shader(vertexFile, fragmentFile)
{

	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid. ");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
	uniforms[VIEW_PROJECTION_U] = glGetUniformLocation(program, "viewProjection");
	uniforms[JOINT_TRANSFORMS_U] = glGetUniformLocation(program, "jointTransforms");
}

void AnimationShader::update(const Transform& transform, const Camera& camera, std::vector<glm::mat4> jointVector)
{
	glm::mat4 model = transform.getModel();
	glm::mat4 viewProjection = camera.GetViewProjection();
	glm::mat4 jointTransforms[MAX_JOINTS];
	for (unsigned int i = 0; i < (jointVector.size() < MAX_JOINTS ? jointVector.size() : MAX_JOINTS); ++i)
	{
		jointTransforms[i] = jointVector[i];
	}

	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(uniforms[VIEW_PROJECTION_U], 1, GL_FALSE, &viewProjection[0][0]);
	glUniformMatrix4fv(uniforms[JOINT_TRANSFORMS_U], MAX_JOINTS, GL_FALSE, glm::value_ptr(jointTransforms[0]));

}

AnimationShader::~AnimationShader()
{
	glDeleteProgram(program);
}