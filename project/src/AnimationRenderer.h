#pragma once

#include <set>

#include "Camera.h"
#include "AnimatedRenderable.h"

static const unsigned int MAX_JOINTS_MODEL = 50;

class AnimationRenderer {
private:
	Camera* camera;
	Shader* shader;
	std::set<AnimatedRenderable*> renderables;
	std::vector<glm::mat4> jointVector;

public:
	AnimationRenderer();
	AnimationRenderer(Camera* camera);
	~AnimationRenderer();

	void load(AnimatedRenderable* renderable);
	void unload(AnimatedRenderable* renderable);

	void render();

	void setShader(Shader* shader);
	Shader* getShader();
};

