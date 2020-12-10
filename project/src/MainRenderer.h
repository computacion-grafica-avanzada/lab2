#pragma once
#include "Camera.h"
#include "Renderer.h"
#include "AnimationRenderer.h"
#include "WaterRenderer.h"
#include "buffers/WaterFrameBuffer.h"
#include <set>

class MainRenderer {
	static Camera* camera;

	static std::set<Renderer*> renderers;
	static std::set<AnimationRenderer*> animationRenderers;
	static std::set<WaterRenderer*> waterRenderers;
	static WaterFrameBuffer* waterFrameBuffer;

public:
	static void init();
	static void init(Camera* camera);

	static void load(Renderer* renderer);
	static void unload(Renderer* renderer);

	static void load(AnimationRenderer* renderer);
	static void unload(AnimationRenderer* renderer);

	static void load(WaterRenderer* renderer);
	static void unload(WaterRenderer* renderer);

	static void enable_culling();
	static void disable_culling();

	static void render();
};