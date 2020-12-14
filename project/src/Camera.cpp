#include "Camera.h"
//#include "Character.h"
#include "MainRenderer.h"
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>

Camera::Camera(Character* player, float fov, float aspectRatio, float nearClip, float farClip) {
	this->player = player;
	setPerspective(fov, aspectRatio, nearClip, farClip);
	InitViewMatrix();
}
void Camera::InitViewMatrix() {
	front = glm::vec3(0, 0, -1);
	worldUp = glm::vec3(0, 1, 0);
	up = worldUp;

	yaw = -90.0f;
	zoom = 150.f;
	pitch = 0.f;
	aap = 180.f;
	UpdateVectors();
}

void Camera::calculatePosition() {
	float horizontalDistance = zoom * cos(glm::radians(pitch));
	float verticalDistance = zoom * sin(glm::radians(pitch));

	yaw = 180 - aap;
	float offsetX = horizontalDistance * sin(glm::radians(aap));
	float offsetZ = horizontalDistance * cos(glm::radians(aap));

	this->position = glm::vec3(
		this->player->getPosition().x - offsetX,
		this->player->getPosition().y + verticalDistance,
		this->player->getPosition().z - offsetZ
	);
}

glm::mat4 Camera::GetProjectionMatrix() {
	return projectionMatrix;
}
void Camera::moveCameraDown() {
	float camDistance = 2 * (this->position.y - 4); //waterHeight
	glm::vec3 invertedCam = this->position - glm::vec3(0, camDistance, 0);

	float playerDistance = 2 * (player->getPosition().y - 4); //waterHeight
	glm::vec3 invertedPlayer = player->getPosition() - glm::vec3(0, playerDistance, 0);

	glm::mat4 uno = glm::lookAt(this->position, player->getPosition(), this->up);
	glm::mat4 dos = glm::lookAt(invertedCam, invertedPlayer, this->up);
	
	viewMatrix = glm::lookAt(invertedCam, invertedPlayer, this->up);
}

void Camera::moveCameraUp() {
	viewMatrix = glm::lookAt(this->position, player->getPosition(), this->up);
}

glm::vec3 Camera::GetPosition() {
	return position;
}
glm::vec3 Camera::GetFront() {
	return front;
}
glm::vec3 Camera::GetUp() {
	return up;
}
glm::vec3 Camera::GetRight() {
	return right;
}
void Camera::setPitch(float pitch) {
	this->pitch = pitch;
}

void Camera::updatePitch(float delta) {
	pitch += (delta * sensitivity);
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < 0.f)
		pitch = 0.f;
}

void Camera::setAap(float delta) {
	aap += (delta * sensitivity);
	aap = fmodf(aap, 360);
}

void Camera::SetFront(glm::vec3 front) {
	this->front = front;
	UpdateVectors();
}

float Camera::GetPitch() {
	return pitch;
}
void Camera::setYaw(float delta) {
	this->yaw = yaw;
	UpdateVectors();
}
float Camera::GetYaw() {
	return yaw;
}
void Camera::UpdateVectors() {
	calculatePosition();
	this->front = player->getPosition() - this->position;
	this->front.y = 0;
	this->front = glm::normalize(this->front);
	viewMatrix = glm::lookAt(this->position, player->getPosition(), this->up);
}

glm::mat4 Camera::GetModelMatrix(bool isCharacter) {
	Character* character = MainRenderer::getCharacter();
	glm::mat4 identityModelMatrix(1.0);
	glm::mat4 modelMatrix = identityModelMatrix;
	if (isCharacter) {
		Direction direction = character->getDirection();

		float rot2 = acos(glm::dot(front,glm::vec3(1,0,0))) * (180 / M_PI);

		glm::vec3 ref(1, 0, 0);
		glm::vec3 cross = glm::cross(ref, front);
		float dot = glm::dot(ref, front);
		float det = glm::dot(up, cross);
		float rot = atan2(det, dot);

		modelMatrix = glm::translate(modelMatrix, character->getPosition());
		switch (direction) {
			case Direction::FRONT:
				modelMatrix = glm::rotate(modelMatrix, rot, up);
				prevRot = rot;
				character->setDirection(Direction::NONE);
				break;
			case Direction::BACK:
				rot += glm::radians(180.0f);
				modelMatrix = glm::rotate(modelMatrix, rot, up);
				prevRot = rot;
				character->setDirection(Direction::NONE);
				break;
			case Direction::LEFT:
				rot += glm::radians(90.0f);
				modelMatrix = glm::rotate(modelMatrix, rot, up);
				prevRot = rot;
				character->setDirection(Direction::NONE);
				break;
			case Direction::RIGHT:
				rot += glm::radians(-90.0f);
				modelMatrix = glm::rotate(modelMatrix, rot, up);
				prevRot = rot;
				character->setDirection(Direction::NONE);
				break;
			case Direction::NONE:
				modelMatrix = glm::rotate(modelMatrix, prevRot, up);
				break;
		}
	}
	return modelMatrix;
}

glm::mat4 Camera::GetViewMatrix() {
	return viewMatrix;
}

float Camera::GetFieldOfView() {
	return fieldOfView;
}
void Camera::SetFieldOfView(float fov) {
	setPerspective(fov, aspectRatio, nearClip, farClip);
}

float Camera::GetAspectRatio() {
	return aspectRatio;
}
void Camera::SetAspectRatio(float aspectRatio) {
	this->aspectRatio = aspectRatio;
	resetCamera();
}
float Camera::GetNearClip() {
	return nearClip;
}
void Camera::SetNearClip(float nearClip) {
	this->nearClip = nearClip;
	resetCamera();
}
float Camera::GetFarClip() {
	return farClip;
}
void Camera::SetFarClip(float farClip) {
	this->farClip = farClip;
	resetCamera();
}

void Camera::resetCamera() {
	setPerspective(fieldOfView, aspectRatio, nearClip, farClip);
	InitViewMatrix();
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float nearClip, float farClip) {
	this->fieldOfView = fieldOfView;
	this->aspectRatio = aspectRatio;
	this->nearClip = nearClip;
	this->farClip = farClip;

	projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearClip, farClip);
}

void Camera::setZoom(float delta) {
	this->zoom -= delta;
	if (this->zoom <= 1.0f) this->zoom = 1.f;
}