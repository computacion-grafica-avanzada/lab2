#pragma once
#include "Light.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "buffers/VertexArray.h"
#include "buffers/WaterFrameBuffer.h"
#include "Display.h"
#include "ITickable.h"
#include <set>

class WaterRenderer : ITickable {
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

	void tick(float time);
	void render(std::set<Light*> lights, WaterFrameBuffer* waterFrameBuffer);
};
