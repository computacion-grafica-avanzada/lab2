#include "Light.h"
#include "MainRenderer.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
	this->position = position;
	this->color = color;

	this->time = 15.f;
	MainRenderer::load(this);
}

Light::~Light() {
	MainRenderer::unload(this);
}

glm::vec3 Light::getPosition() {
	return position;
}

glm::vec3 Light::getColor() {
	return color;
}

void Light::setPosition(glm::vec3 position) {
	this->position = position;
}

void Light::setColor(glm::vec3 color) {
	this->color = color;
}

void Light::tick() {
	time += TimeFrame::deltaTime;
	time = fmod(time, 60.0f);
	this->position = glm::vec3(
		radius * cosf(time * speed),
		radius * sinf(time * speed),
		0
	);
}