#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "Shader.h"
#include "MainRenderer.h"

void initIsland(Camera* camera, Shader* shader);
void initTowers(Camera* camera, Shader* shader);
void initTrees(Camera* camera, Shader* shader);
void initStones(Camera* camera, Shader* shader);