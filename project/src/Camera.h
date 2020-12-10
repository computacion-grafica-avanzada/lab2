#pragma once

#include <glm/glm.hpp>
#include "Character.h"

class Camera {

	Character* player;
	float aspectRatio, nearClip, farClip;
	float fieldOfView;

	glm::mat4 projectionMatrix, viewMatrix;
	glm::vec3 position, front, worldUp, up, right;

	void InitViewMatrix();

	float yaw, pitch, fov, zoom;
public:
	void UpdateVectors();
	float angle;
	Camera(Character* player, float fov, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);

	glm::mat4 GetProjectionMatrix();

	void calculatePosition();

	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	glm::vec3 GetUp();
	glm::vec3 GetRight();
	void SetFront(glm::vec3 front);

	void SetPitch(float pitch);
	float GetPitch();
	void SetYaw(float yaw);
	float GetYaw();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetModelMatrix(bool isCharacter);

	float GetFieldOfView();
	void SetFieldOfView(float fov);
	float GetAspectRatio();
	void SetAspectRatio(float aspectRatio);
	float GetNearClip();
	void SetNearClip(float nearClip);
	float GetFarClip();
	void SetFarClip(float farClip);

private:
	void ResetCamera();
	void SetOrthographic(float size, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);
	void SetPerspective(float fieldOfView, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);
};