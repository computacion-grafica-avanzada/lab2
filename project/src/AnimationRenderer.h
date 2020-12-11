#pragma once

#include <set>

#include "Camera.h"
#include "Renderable.h"

static const unsigned int MAX_JOINTS_MODEL = 50;

class AnimationRenderer {
private:
	Camera* camera;
	Shader* shader;
	std::set<Renderable*> renderables;
	std::vector<glm::mat4> jointVector;

public:
	AnimationRenderer();
	AnimationRenderer(Camera* camera);
	~AnimationRenderer();

	void load(Renderable* renderable);
	void unload(Renderable* renderable);

	void render();

	void setShader(Shader* shader);
	Shader* getShader();
};

