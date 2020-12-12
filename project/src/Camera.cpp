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
void Camera::setPitch(float delta) {
	pitch += (delta * sensitivity);
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
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
	//glm::vec3 front;
	//front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	//front.y = sin(glm::radians(this->pitch));
	//front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	////front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(0.0f));
	////front.y = sin(glm::radians(0.0f));
	////front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(0.0f));

	//this->front = glm::normalize(front);
	//this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	//this->up = glm::normalize(glm::cross(this->right, this->front));


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

		//float rot2 = glm::radians(-90.f);
		//cout << zoom << " " << rot2 << " " << aap << " " << rot << " (" << position.x << " " << position.y << " " << position.z << ") " << front.x << " " << front.y << " " << front.z << endl;

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
		//modelMatrix = glm::rotate(modelMatrix, glm::radians(90.f), up);
		//modelMatrix = glm::translate(modelMatrix, -character->getPosition());
		//modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
	}
	return modelMatrix;
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(
		this->position,
		this->player->getPosition(),
		this->up
	);
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