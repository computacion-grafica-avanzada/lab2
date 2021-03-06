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
	glm::vec4 clipPlane;
	bool clipPlaneEnabled;

	float blendFactor;
	glm::vec3 start, end;

public:
	SkyboxRenderer(Camera*);
	~SkyboxRenderer();

	void enableClipPlane(glm::vec4 clipPlane);
	void disableClipPlane();
	void render();

	glm::vec3 getSkyColor();

	void tick(float time);
};