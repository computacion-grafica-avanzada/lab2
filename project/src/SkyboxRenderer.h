#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "ITickable.h"
#include "Display.h"
#include "buffers/VertexArray.h"
#include <vector>

class SkyboxRenderer : ITickable {
	Shader* shader;
	Camera* camera;
	VertexArray* vertexArray;
	Texture* cubeMap;
	glm::vec4 clipPlane;
	bool clipPlaneEnabled;
	float time;

	float blendFactor;
	glm::vec3 start, end;
	void skyColors();

public:
	SkyboxRenderer(Camera*);
	~SkyboxRenderer();

	void enableClipPlane(glm::vec4 clipPlane);
	void disableClipPlane();
	void render();

	void tick();
};