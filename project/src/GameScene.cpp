#include "GameScene.h"
#include "Collider.h"

void initIsland(Camera* camera, Shader* world, CollisionManager* collisionManager) {
	initTowers(camera, world, collisionManager);
	initTrees(camera, world, collisionManager);
	initStones(camera, world);
}

void initStones(Camera* camera, Shader* world) {

	// SE island
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(200, 30, 300));
	model = glm::scale(model, glm::vec3(0.2));
	//model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* rock = new Renderer(camera, false, model);
	rock->loadObj("../models/Stone/stone.obj");
	rock->setShader(world);

	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 30, 400));
	model = glm::scale(model, glm::vec3(0.3));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* rock2 = new Renderer(camera, false, model);
	rock2->renderables = rock->renderables;
	rock2->setShader(world);

	model = glm::translate(glm::mat4(1.0), glm::vec3(400, 30, 300));
	model = glm::scale(model, glm::vec3(0.4));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* rock3 = new Renderer(camera, false, model);
	rock3->renderables = rock->renderables;
	rock3->setShader(world);

	// NE island

	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 30, -400));
	model = glm::scale(model, glm::vec3(0.3));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* rock4 = new Renderer(camera, false, model);
	rock4->renderables = rock->renderables;
	rock4->setShader(world);

	model = glm::translate(glm::mat4(1.0), glm::vec3(400, 30, -300));
	model = glm::scale(model, glm::vec3(0.4));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* rock5 = new Renderer(camera, false, model);
	rock5->renderables = rock->renderables;
	rock5->setShader(world);

	// NO island

	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, -400));
	model = glm::scale(model, glm::vec3(0.4));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* rock6 = new Renderer(camera, false, model);
	rock6->renderables = rock->renderables;
	rock6->setShader(world);
}

void initTrees(Camera* camera, Shader* world, CollisionManager* collisionManager) {
	float height = 125.f;
	//glm::vec3 scale(200, height, 200);
	glm::vec3 scale(height);

	// SE tower
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0, 20, 0));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* tree = new Renderer(camera, false, model);
	Collider* treeCollider = new Collider(4, 2, 25.0f, tree->getHighestVertix().y);
	treeCollider->pos = tree->getAverageVertix();
	collisionManager->addObjectCollider(treeCollider);
	tree->loadObj("../models/Trees/final.obj");
	tree->setShader(world);

	// SE island
	height = 140.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 10, 200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* tree2 = new Renderer(camera, false, model);
	Collider* tree2Collider = new Collider(5, 2, 25.0f, tree2->getHighestVertix().y);
	tree2Collider->pos = tree2->getAverageVertix();
	collisionManager->addObjectCollider(tree2Collider);
	tree2->renderables = tree->renderables;
	tree2->setShader(world);

	// NE island
	height = 155.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 0, -200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(135.f), glm::vec3(0, 1, 0));
	Renderer* tree3 = new Renderer(camera, false, model);
	Collider* tree3Collider = new Collider(6, 2, 25.0f, tree3->getHighestVertix().y);
	tree3Collider->pos = tree3->getAverageVertix();
	collisionManager->addObjectCollider(tree3Collider);
	tree3->renderables = tree->renderables;
	tree3->setShader(world);

	height = 170.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(200, 0, -300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 1, 0));
	Renderer* tree4 = new Renderer(camera, false, model);
	Collider* tree4Collider = new Collider(7, 2, 25.0f, tree4->getHighestVertix().y);
	tree4Collider->pos = tree4->getAverageVertix();
	collisionManager->addObjectCollider(tree4Collider);
	tree4->renderables = tree->renderables;
	tree4->setShader(world);

	// NO island
	height = 185.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 0, -200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(225.f), glm::vec3(0, 1, 0));
	Renderer* tree5 = new Renderer(camera, false, model);
	Collider* tree5Collider = new Collider(8, 2, 25.0f, tree5->getHighestVertix().y);
	tree5Collider->pos = tree5->getAverageVertix();
	collisionManager->addObjectCollider(tree5Collider);
	tree5->renderables = tree->renderables;
	tree5->setShader(world);

	height = 200.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-200, 10, -300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(270.f), glm::vec3(0, 1, 0));
	Renderer* tree6 = new Renderer(camera, false, model);
	Collider* tree6Collider = new Collider(9, 2, 25.0f, tree6->getHighestVertix().y);
	tree6Collider->pos = tree6->getAverageVertix();
	collisionManager->addObjectCollider(tree6Collider);
	tree6->renderables = tree->renderables;
	tree6->setShader(world);

	height = 215.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-400, 30, -300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(315.f), glm::vec3(0, 1, 0));
	Renderer* tree7 = new Renderer(camera, false, model);
	Collider* tree7Collider = new Collider(10, 2, 25.0f, tree7->getHighestVertix().y);
	tree7Collider->pos = tree7->getAverageVertix();
	collisionManager->addObjectCollider(tree7Collider);
	tree7->renderables = tree->renderables;
	tree7->setShader(world);

	// SO island
	height = 230.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 0, 200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(360.f), glm::vec3(0, 1, 0));
	Renderer* tree8 = new Renderer(camera, false, model);
	Collider* tree8Collider = new Collider(11, 2, 25.0f, tree8->getHighestVertix().y);
	tree8Collider->pos = tree8->getAverageVertix();
	collisionManager->addObjectCollider(tree8Collider);
	tree8->renderables = tree->renderables;
	tree8->setShader(world);

	height = 245.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-200, 0, 300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* tree9 = new Renderer(camera, false, model);
	Collider* tree9Collider = new Collider(12, 2, 25.0f, tree9->getHighestVertix().y);
	tree9Collider->pos = tree9->getAverageVertix();
	collisionManager->addObjectCollider(tree9Collider);
	tree9->renderables = tree->renderables;
	tree9->setShader(world);

	height = 260.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-400, 0, 300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* tree10 = new Renderer(camera, false, model);
	Collider* tree10Collider = new Collider(13, 2, 25.0f, tree10->getHighestVertix().y);
	tree10Collider->pos = tree10->getAverageVertix();
	collisionManager->addObjectCollider(tree10Collider);
	tree10->renderables = tree->renderables;
	tree10->setShader(world);

	height = 275.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, 400));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(135.f), glm::vec3(0, 1, 0));
	Renderer* tree11 = new Renderer(camera, false, model);
	Collider* tree11Collider = new Collider(14, 2, 25.0f, tree11->getHighestVertix().y);
	tree11Collider->pos = tree11->getAverageVertix();
	collisionManager->addObjectCollider(tree11Collider);
	tree11->renderables = tree->renderables;
	tree11->setShader(world);
}

void initTowers(Camera* camera, Shader* world, CollisionManager* collisionManager) {

	glm::vec3 scale(0.3);

	// obtain tower mesh
	Renderer* tower = new Renderer(camera, false, glm::mat4(1.0));
	tower->loadObj("../models/Landscapes/tower2.obj");
	MainRenderer::unload(tower);
	Mesh* towerMesh = (*tower->renderables.begin())->getMesh();

	// SE tower
	glm::mat4 modelSE = glm::translate(glm::mat4(1.0), glm::vec3(300, 30, 300));
	modelSE = glm::scale(modelSE, scale);
	modelSE = glm::rotate(modelSE, glm::radians(225.f), glm::vec3(0, 1, 0));
	
	Texture* towerTexSE = new Texture("../models/Tower/Castle_Tower_Tex_sunset.png");
	Renderable* towerBaseSE = new Renderable();
	towerBaseSE->setMesh(towerMesh);
	towerBaseSE->setTexture(towerTexSE, 1);

	Renderer* towerSE = new Renderer(camera, false, modelSE);
	Collider* towerSECollider = new Collider(15, 2, 25.0f, towerSE->getHighestVertix().y);
	towerSECollider->pos = towerSE->getAverageVertix();
	collisionManager->addObjectCollider(towerSECollider);
	towerSE->load(towerBaseSE);
	towerSE->setShader(world);

	// NE tower
	glm::mat4 modelNE = glm::translate(glm::mat4(1.0), glm::vec3(300, 30, -300));
	modelNE = glm::scale(modelNE, scale);
	modelNE = glm::rotate(modelNE, glm::radians(-45.f), glm::vec3(0, 1, 0));

	Texture* towerTexNE = new Texture("../models/Tower/Castle_Tower_Tex_midday.png");
	Renderable* towerBaseNE = new Renderable();
	towerBaseNE->setMesh(towerMesh);
	towerBaseNE->setTexture(towerTexNE, 1);

	Renderer* towerNE = new Renderer(camera, false, modelNE);
	Collider* towerNECollider = new Collider(16, 2, 25.0f, towerNE->getHighestVertix().y);
	towerNECollider->pos = towerNE->getAverageVertix();
	collisionManager->addObjectCollider(towerNECollider);
	towerNE->load(towerBaseNE);
	towerNE->setShader(world);

	// NO tower
	glm::mat4 modelNO = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, -300));
	modelNO = glm::scale(modelNO, scale);
	modelNO = glm::rotate(modelNO, glm::radians(45.f), glm::vec3(0, 1, 0));

	Texture* towerTexNO = new Texture("../models/Tower/Castle_Tower_Tex_morning.png");
	Renderable* towerBaseNO = new Renderable();
	towerBaseNO->setMesh(towerMesh);
	towerBaseNO->setTexture(towerTexNO, 1);

	Renderer* towerNO = new Renderer(camera, false, modelNO);
	Collider* towerNOCollider = new Collider(17, 2, 25.0f, towerNO->getHighestVertix().y);
	towerNOCollider->pos = towerNO->getAverageVertix();
	collisionManager->addObjectCollider(towerNOCollider);
	towerNO->load(towerBaseNO);
	towerNO->setShader(world);

	// SO tower
	glm::mat4 modelSO = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, 300));
	modelSO = glm::scale(modelSO, scale);
	modelSO = glm::rotate(modelSO, glm::radians(-225.f), glm::vec3(0, 1, 0));

	Texture* towerTexSO = new Texture("../models/Tower/Castle_Tower_Tex_night.png");
	Renderable* towerBaseSO = new Renderable();
	towerBaseSO->setMesh(towerMesh);
	towerBaseSO->setTexture(towerTexSO, 1);

	Renderer* towerSO = new Renderer(camera, false, modelSO);
	Collider* towerSOCollider = new Collider(18, 2, 25.0f, towerSO->getHighestVertix().y);
	towerSOCollider->pos = towerSO->getAverageVertix();
	collisionManager->addObjectCollider(towerSOCollider);
	towerSO->load(towerBaseSO);
	towerSO->setShader(world);
}
