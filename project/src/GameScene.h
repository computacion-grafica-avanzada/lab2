#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "Shader.h"
#include "MainRenderer.h"
#include "CollisionManager.h"

void initIsland(Camera* camera, Shader* shader, CollisionManager* collisionManager);
void initTowers(Camera* camera, Shader* shader, CollisionManager* collisionManager);
void initTrees(Camera* camera, Shader* shader, CollisionManager* collisionManager);
void initStones(Camera* camera, Shader* shader, CollisionManager* collisionManager);