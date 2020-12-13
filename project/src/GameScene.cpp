#include "GameScene.h"

void initIsland(Camera* camera, Shader* world) {
	initTowers(camera, world);
}

void initTowers(Camera* camera, Shader* world) {

	glm::vec3 scale(0.5, 0.5, 0.5);

	glm::mat4 modelSE = glm::translate(glm::mat4(1.0), glm::vec3(300, 30, 300));
	modelSE = glm::scale(modelSE, scale);
	modelSE = glm::rotate(modelSE, glm::radians(225.f), glm::vec3(0, 1, 0));
	Renderer* towerSE = new Renderer(camera, false, modelSE);
	towerSE->loadObj("../models/Landscapes/tower2.obj");
	towerSE->setShader(world);

	Mesh* tower = (*towerSE->renderables.begin())->getMesh();
	Texture* towerTex = new Texture("../models/Tower/Castle_Tower_Tex.jpg");
	Renderable* towerBase = new Renderable();
	towerBase->setMesh(tower);
	towerBase->setTexture(towerTex, 1);

	glm::mat4 modelNE = glm::translate(glm::mat4(1.0), glm::vec3(300, 30, -300));
	modelNE = glm::scale(modelNE, scale);
	modelNE = glm::rotate(modelNE, glm::radians(-45.f), glm::vec3(0, 1, 0));
	Renderer* towerNE = new Renderer(camera, false, modelNE);
	towerNE->load(towerBase);
	towerNE->setShader(world);

	glm::mat4 modelNO = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, -300));
	modelNO = glm::scale(modelNO, scale);
	modelNO = glm::rotate(modelNO, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* towerNO = new Renderer(camera, false, modelNO);
	towerNO->load(towerBase);
	towerNO->setShader(world);

	glm::mat4 modelSO = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, 300));
	modelSO = glm::scale(modelSO, scale);
	modelSO = glm::rotate(modelSO, glm::radians(-225.f), glm::vec3(0, 1, 0));
	Renderer* towerSO = new Renderer(camera, false, modelSO);
	towerSO->load(towerBase);
	towerSO->setShader(world);
}
