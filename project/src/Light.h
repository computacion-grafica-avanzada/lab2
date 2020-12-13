#pragma once
#include "glm/glm.hpp"
#include "ITickable.h"
#include "TimeFrame.h"

class Light : ITickable {
	glm::vec3 position;
	glm::vec3 color;

	float time = 15.f;
	float radius = 400.f;
	float speed = M_PI / 30.f;

public:
	Light(glm::vec3 position, glm::vec3 color);
	~Light();
	glm::vec3 getPosition();
	glm::vec3 getColor();
	void setPosition(glm::vec3);
	void setColor(glm::vec3);
	void tick();
};