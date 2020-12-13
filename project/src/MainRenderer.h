#pragma once
#include "Light.h"
#include "Camera.h"
#include "Renderer.h"
#include "Character.h"
#include "GuiRenderer.h"
#include "WaterRenderer.h"
#include "SkyboxRenderer.h"
#include "buffers/WaterFrameBuffer.h"
#include <set>

class MainRenderer {
	static Camera* camera;
	static Character* character;

	static std::set<Light*> lights;
	static std::set<Renderer*> renderers;
	static std::set<GuiRenderer*> guiRenderers;
	static std::set<WaterRenderer*> waterRenderers;
	static SkyboxRenderer* skybox;
	static WaterFrameBuffer* waterFrameBuffer;

public:
	static void init();
	static void init(Camera* camera);

	static void load(Light* renderer);
	static void unload(Light* renderer);

	static void load(Renderer* renderer);
	static void unload(Renderer* renderer);
	
	static void load(GuiRenderer* renderer);
	static void unload(GuiRenderer* renderer);

	static void load(WaterRenderer* renderer);
	static void unload(WaterRenderer* renderer);

	static void enable_culling();
	static void disable_culling();

	static void render();

	static Character* getCharacter();
	static void setCharacter(Character* character);
};
