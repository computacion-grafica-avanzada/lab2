#pragma once

#include <set>

#include "Camera.h"
#include "Renderer.h"
#include "AnimationRenderer.h"
#include "Character.h"
#include "GuiRenderer.h"
#include "WaterRenderer.h"
#include "buffers/WaterFrameBuffer.h"

class MainRenderer {
	static Camera* camera;
	static Character* character;

	static std::set<Renderer*> renderers;
	static std::set<AnimationRenderer*> animationRenderers;
	static std::set<GuiRenderer*> guiRenderers;
	static std::set<WaterRenderer*> waterRenderers;
	static WaterFrameBuffer* waterFrameBuffer;

public:
	static void init();
	static void init(Camera* camera);

	static void load(Renderer* renderer);
	static void unload(Renderer* renderer);

	static void load(GuiRenderer* renderer);
	static void unload(GuiRenderer* renderer);

	static void load(AnimationRenderer* renderer);
	static void unload(AnimationRenderer* renderer);

	static void load(WaterRenderer* renderer);
	static void unload(WaterRenderer* renderer);

	static void enable_culling();
	static void disable_culling();

	static void render();

	static Character* getCharacter();
	static void setCharacter(Character* character);
};
