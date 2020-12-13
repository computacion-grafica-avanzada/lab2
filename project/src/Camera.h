#pragma once

#include <glm/glm.hpp>
#include "Character.h"

class Camera {

	float sensitivity = 0.1f;
	Character* player;
	float aspectRatio, nearClip, farClip;
	float fieldOfView;

	glm::mat4 projectionMatrix, viewMatrix;
	glm::vec3 position, front, worldUp, up, right;

	void InitViewMatrix();

	float yaw, pitch, fov;

	float prevRot;
public:
	void UpdateVectors();
	float angle, aap, zoom;
	Camera(Character* player, float fov, float aspectRatio, float nearClip = 0.1f, float farClip = 12000.0f);

	glm::mat4 GetProjectionMatrix();

	void calculatePosition();

	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	glm::vec3 GetUp();
	glm::vec3 GetRight();
	void SetFront(glm::vec3 front);

	void setPitch(float delta);
	void setAap(float delta);

	float GetPitch();
	void setYaw(float delta);
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

	void setZoom(float delta);
	void resetCamera();
private:
	void setPerspective(float fieldOfView, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);
};