#include "Camera.h"
#include "Character.h"
#include "MainRenderer.h"
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>

Camera::Camera(Character* player, float fov, float aspectRatio, float nearClip, float farClip) {
	this->player = player;
	SetPerspective(fov, aspectRatio, nearClip, farClip);
	InitViewMatrix();
}
void Camera::InitViewMatrix() {
	//position = glm::vec3(-50, 75, 100);
	//position = glm::vec3(0, 0, 10);
	front = glm::vec3(0, 0, -1);
	worldUp = glm::vec3(0, 1, 0);
	yaw = -90.0f;
	pitch = 0.0f;
	angle = 0;
	zoom = 150.f;
	UpdateVectors();
}

void Camera::calculatePosition() {
	float horizontalDistance = zoom * cos(glm::radians(pitch));
	float verticalDistance = zoom * sin(glm::radians(pitch));

	float theta = 180 - yaw;
	float offsetX = horizontalDistance * sin(glm::radians(theta));
	float offsetZ = horizontalDistance * cos(glm::radians(theta));

	this->position = glm::vec3(
		this->player->position.x - offsetX,
		this->player->position.y + verticalDistance,
		this->player->position.z - offsetZ
	);
}

glm::mat4 Camera::GetProjectionMatrix() {
	return projectionMatrix;
}
void Camera::SetPosition(glm::vec3 position) {
	this->position = position;
	viewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);
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
void Camera::SetPitch(float pitch) {
	this->pitch = pitch;
	UpdateVectors();
}

void Camera::SetFront(glm::vec3 front) {
	this->front = front;
	UpdateVectors();
}

float Camera::GetPitch() {
	return pitch;
}
void Camera::SetYaw(float yaw) {
	this->yaw = yaw;
	UpdateVectors();
}
float Camera::GetYaw() {
	return yaw;
}
void Camera::UpdateVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));

	calculatePosition();
	//viewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);
	viewMatrix = glm::lookAt(this->position, player->position, this->up);
}

glm::mat4 Camera::GetModelMatrix(bool isCharacter) {
	Character* character = MainRenderer::getCharacter();
	glm::mat4 identityModelMatrix(1.0);
	glm::mat4 modelMatrix = identityModelMatrix;
	if (isCharacter) {
		Direction direction = character->getDirection();
		modelMatrix = glm::translate(modelMatrix, character->getPosition());
		switch (direction) {
			case LEFT:
				modelMatrix = glm::rotate(modelMatrix , glm::radians(45.0f), glm::vec3(0, 1, 0));
				break;
			case RIGHT:
				modelMatrix = glm::rotate(modelMatrix , glm::radians(-45.0f), glm::vec3(0, 1, 0));
				break;
		}
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
	}
	return modelMatrix;
}

glm::mat4 Camera::GetViewMatrix() {
	Character* character = MainRenderer::getCharacter();
	return glm::lookAt(
		this->position,
		character->getPosition(),
		this->up
	);
}

float Camera::GetFieldOfView() {
	return fieldOfView;
}
void Camera::SetFieldOfView(float fov) {
	SetPerspective(fov, aspectRatio, nearClip, farClip);
}

float Camera::GetAspectRatio() {
	return aspectRatio;
}
void Camera::SetAspectRatio(float aspectRatio) {
	this->aspectRatio = aspectRatio;
	ResetCamera();
}
float Camera::GetNearClip() {
	return nearClip;
}
void Camera::SetNearClip(float nearClip) {
	this->nearClip = nearClip;
	ResetCamera();
}
float Camera::GetFarClip() {
	return farClip;
}
void Camera::SetFarClip(float farClip) {
	this->farClip = farClip;
	ResetCamera();
}

void Camera::ResetCamera() {
	SetPerspective(fieldOfView, aspectRatio, nearClip, farClip);
}

void Camera::SetPerspective(float fieldOfView, float aspectRatio, float nearClip, float farClip) {
	this->fieldOfView = fieldOfView;
	this->aspectRatio = aspectRatio;
	this->nearClip = nearClip;
	this->farClip = farClip;

	projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearClip, farClip);
	//projectionMatrix = glm::infinitePerspective(fieldOfView, aspectRatio, nearClip);
}
