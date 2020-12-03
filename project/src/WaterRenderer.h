#pragma once

#include "Camera.h"
#include "Water.h"
#include "buffers/WaterFrameBuffer.h"
#include <set>

class WaterRenderer {
private:
	Camera* camera;
	std::set<Water*> waters;

public:
	WaterRenderer();
	WaterRenderer(Camera* camera);
	~WaterRenderer();

	void load(Water* water);
	void unload(Water* water);

	void render(WaterFrameBuffer* waterFrameBuffer);
};