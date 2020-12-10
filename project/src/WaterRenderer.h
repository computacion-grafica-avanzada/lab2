#pragma once

#include "Camera.h"
#include "Water.h"
#include "buffers/WaterFrameBuffer.h"
#include "TimeFrame.h"
#include <set>

class WaterRenderer {
private:
	Camera* camera;
	Shader* shader;
	Texture* dudv,* normal;
	VertexArray* vertexArray;
	float height;
	glm::vec2 scale;
	float moveFactor;
	float textureTiling;
	float distortionStrength;
	float moveSpeed;
	float specularPower;

public:


	WaterRenderer(Camera* camera, Shader* shader, Texture* dudv, Texture* normal);
	WaterRenderer(Camera* camera);
	~WaterRenderer();

	void render(WaterFrameBuffer* waterFrameBuffer);
};
