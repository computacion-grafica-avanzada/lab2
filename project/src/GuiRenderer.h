#pragma once
#include <set>
#include <vector>
#include "glm/glm.hpp"
#include "Shader.h"
#include "Texture.h"
#include "buffers/VertexArray.h"

struct GuiTexture {
	Texture* tex;
	glm::vec2 position;
	glm::vec2 scale;
};

class GuiRenderer {
	Shader* shader;
	VertexArray* vertexArray;
	std::set<GuiTexture*> guis;

public:
	GuiRenderer(Shader* shader);
	~GuiRenderer();

	void load(GuiTexture* gui);
	void unload(GuiTexture* gui);

	void render();
};