#pragma once
#pragma once

#include "Camera.h"
#include "Water.h"
#include "buffers/WaterFrameBuffer.h"
#include <set>

static const unsigned int MAX_JOINTS = 50;

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

