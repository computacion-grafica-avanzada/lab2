#include "GameScene.h"
#include "Collider.h"

void initIsland(Camera* camera, Shader* world, CollisionManager* collisionManager) {
	initTowers(camera, world, collisionManager);
	initTrees(camera, world, collisionManager);
	initStones(camera, world, collisionManager);
}

void initStones(Camera* camera, Shader* world,  CollisionManager* collisionManager) {

	// SE island
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(200, 30, 300));
	model = glm::scale(model, glm::vec3(0.2));
	//model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* rock = new Renderer(camera, false, model);
	rock->loadObj("../models/Stone/stone.obj");
	rock->setShader(world);
	Collider* rockCollider = new Collider(15, 2, 2.0f, rock->getHighestVertix().y);
	rockCollider->pos = glm::vec3(200, 30, 300);
	collisionManager->addObjectCollider(rockCollider);

	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 30, 400));
	model = glm::scale(model, glm::vec3(0.3));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* rock2 = new Renderer(camera, false, model);
	rock2->renderables = rock->renderables;
	rock2->setShader(world);
	Collider* rock2Collider = new Collider(15, 2, 2.0f, rock2->getHighestVertix().y);
	rock2Collider->pos = glm::vec3(300, 30, 400);
	collisionManager->addObjectCollider(rock2Collider);

	model = glm::translate(glm::mat4(1.0), glm::vec3(400, 30, 300));
	model = glm::scale(model, glm::vec3(0.4));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* rock3 = new Renderer(camera, false, model);
	rock3->renderables = rock->renderables;
	rock3->setShader(world);
	Collider* rock3Collider = new Collider(15, 2, 2.0f, rock3->getHighestVertix().y);
	rock3Collider->pos = glm::vec3(400, 30, 300);
	collisionManager->addObjectCollider(rock3Collider);

	// NE island

	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 30, -400));
	model = glm::scale(model, glm::vec3(0.3));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* rock4 = new Renderer(camera, false, model);
	rock4->renderables = rock->renderables;
	rock4->setShader(world);
	Collider* rock4Collider = new Collider(15, 2, 2.0f, rock4->getHighestVertix().y);
	rock4Collider->pos = glm::vec3(300, 30, -400);
	collisionManager->addObjectCollider(rock4Collider);

	model = glm::translate(glm::mat4(1.0), glm::vec3(400, 30, -300));
	model = glm::scale(model, glm::vec3(0.4));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* rock5 = new Renderer(camera, false, model);
	rock5->renderables = rock->renderables;
	rock5->setShader(world);
	Collider* rock5Collider = new Collider(15, 2, 2.0f, rock5->getHighestVertix().y);
	rock5Collider->pos = glm::vec3(400, 30, -300);
	collisionManager->addObjectCollider(rock5Collider);

	// NO island

	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, -400));
	model = glm::scale(model, glm::vec3(0.4));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* rock6 = new Renderer(camera, false, model);
	rock6->renderables = rock->renderables;
	rock6->setShader(world);
	Collider* rock6Collider = new Collider(15, 2, 2.0f, rock6->getHighestVertix().y);
	rock6Collider->pos = glm::vec3(-300, 30, -400);
	collisionManager->addObjectCollider(rock6Collider);
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
	Collider* treeCollider = new Collider(4, 2, 0.4f, height);
	treeCollider->pos = glm::vec3(0, 20, 0);
	collisionManager->addObjectCollider(treeCollider);
	tree->loadObj("../models/Trees/final.obj");
	tree->setShader(world);

	// SE island
	height = 140.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 10, 200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* tree2 = new Renderer(camera, false, model);
	Collider* tree2Collider = new Collider(5, 2, 0.4f, height);
	tree2Collider->pos = glm::vec3(300, 10, 200);
	collisionManager->addObjectCollider(tree2Collider);
	tree2->renderables = tree->renderables;
	tree2->setShader(world);

	// NE island
	height = 155.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 0, -200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(135.f), glm::vec3(0, 1, 0));
	Renderer* tree3 = new Renderer(camera, false, model);
	Collider* tree3Collider = new Collider(6, 2, 0.4f, height);
	tree3Collider->pos = glm::vec3(300, 0, -200);
	collisionManager->addObjectCollider(tree3Collider);
	tree3->renderables = tree->renderables;
	tree3->setShader(world);

	height = 170.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(200, 0, -300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 1, 0));
	Renderer* tree4 = new Renderer(camera, false, model);
	Collider* tree4Collider = new Collider(7, 2, 0.4f, height);
	tree4Collider->pos = glm::vec3(200, 0, -300);
	collisionManager->addObjectCollider(tree4Collider);
	tree4->renderables = tree->renderables;
	tree4->setShader(world);

	// NO island
	height = 185.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 0, -200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(225.f), glm::vec3(0, 1, 0));
	Renderer* tree5 = new Renderer(camera, false, model);
	Collider* tree5Collider = new Collider(8, 2, 0.4f, height);
	tree5Collider->pos = glm::vec3(-300, 0, -200);
	collisionManager->addObjectCollider(tree5Collider);
	tree5->renderables = tree->renderables;
	tree5->setShader(world);

	height = 200.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-200, 10, -300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(270.f), glm::vec3(0, 1, 0));
	Renderer* tree6 = new Renderer(camera, false, model);
	Collider* tree6Collider = new Collider(9, 2, 0.4f, height);
	tree6Collider->pos = glm::vec3(-200, 10, -300);
	collisionManager->addObjectCollider(tree6Collider);
	tree6->renderables = tree->renderables;
	tree6->setShader(world);

	height = 215.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-400, 30, -300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(315.f), glm::vec3(0, 1, 0));
	Renderer* tree7 = new Renderer(camera, false, model);
	Collider* tree7Collider = new Collider(10, 2, 0.4f, height);
	tree7Collider->pos = glm::vec3(-400, 30, -300);
	collisionManager->addObjectCollider(tree7Collider);
	tree7->renderables = tree->renderables;
	tree7->setShader(world);

	// SO island
	height = 230.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 0, 200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(360.f), glm::vec3(0, 1, 0));
	Renderer* tree8 = new Renderer(camera, false, model);
	Collider* tree8Collider = new Collider(11, 2, 0.4f, height);
	tree8Collider->pos = glm::vec3(-300, 0, 200);
	collisionManager->addObjectCollider(tree8Collider);
	tree8->renderables = tree->renderables;
	tree8->setShader(world);

	height = 245.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-200, 0, 300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* tree9 = new Renderer(camera, false, model);
	Collider* tree9Collider = new Collider(12, 2, 0.4f, height);
	tree9Collider->pos = glm::vec3(-200, 0, 300);
	collisionManager->addObjectCollider(tree9Collider);
	tree9->renderables = tree->renderables;
	tree9->setShader(world);

	height = 260.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-400, 0, 300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* tree10 = new Renderer(camera, false, model);
	Collider* tree10Collider = new Collider(13, 2, 0.4f, height);
	tree10Collider->pos = glm::vec3(-400, 0, 300);
	collisionManager->addObjectCollider(tree10Collider);
	tree10->renderables = tree->renderables;
	tree10->setShader(world);

	height = 275.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, 400));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(135.f), glm::vec3(0, 1, 0));
	Renderer* tree11 = new Renderer(camera, false, model);
	Collider* tree11Collider = new Collider(14, 2, 0.4f, height);
	tree11Collider->pos = glm::vec3(-300, 30, 400);
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
	Collider* towerSECollider = new Collider(15, 2, 14.0f, towerSE->getHighestVertix().y);
	towerSE->load(towerBaseSE);
	towerSE->setShader(world);
	towerSECollider->pos = glm::vec3(300, 30, 300);
	collisionManager->addObjectCollider(towerSECollider);

	// NE tower
	glm::mat4 modelNE = glm::translate(glm::mat4(1.0), glm::vec3(300, 30, -300));
	modelNE = glm::scale(modelNE, scale);
	modelNE = glm::rotate(modelNE, glm::radians(-45.f), glm::vec3(0, 1, 0));

	Texture* towerTexNE = new Texture("../models/Tower/Castle_Tower_Tex_midday.png");
	Renderable* towerBaseNE = new Renderable();
	towerBaseNE->setMesh(towerMesh);
	towerBaseNE->setTexture(towerTexNE, 1);

	Renderer* towerNE = new Renderer(camera, false, modelNE);
	Collider* towerNECollider = new Collider(16, 2, 14.0f, towerNE->getHighestVertix().y);
	towerNE->load(towerBaseNE);
	towerNE->setShader(world);
	towerNECollider->pos = glm::vec3(300, 30, -300);
	collisionManager->addObjectCollider(towerNECollider);

	// NO tower
	glm::mat4 modelNO = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, -300));
	modelNO = glm::scale(modelNO, scale);
	modelNO = glm::rotate(modelNO, glm::radians(45.f), glm::vec3(0, 1, 0));

	Texture* towerTexNO = new Texture("../models/Tower/Castle_Tower_Tex_morning.png");
	Renderable* towerBaseNO = new Renderable();
	towerBaseNO->setMesh(towerMesh);
	towerBaseNO->setTexture(towerTexNO, 1);

	Renderer* towerNO = new Renderer(camera, false, modelNO);
	Collider* towerNOCollider = new Collider(17, 2, 14.0f, towerNO->getHighestVertix().y);
	towerNO->load(towerBaseNO);
	towerNO->setShader(world);
	towerNOCollider->pos = glm::vec3(-300, 30, -300);
	collisionManager->addObjectCollider(towerNOCollider);

	// SO tower
	glm::mat4 modelSO = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, 300));
	modelSO = glm::scale(modelSO, scale);
	modelSO = glm::rotate(modelSO, glm::radians(-225.f), glm::vec3(0, 1, 0));

	Texture* towerTexSO = new Texture("../models/Tower/Castle_Tower_Tex_night.png");
	Renderable* towerBaseSO = new Renderable();
	towerBaseSO->setMesh(towerMesh);
	towerBaseSO->setTexture(towerTexSO, 1);

	Renderer* towerSO = new Renderer(camera, false, modelSO);
	Collider* towerSOCollider = new Collider(18, 2, 14.0f, towerSO->getHighestVertix().y);
	towerSO->load(towerBaseSO);
	towerSO->setShader(world);
	towerSOCollider->pos = glm::vec3(-300, 30, 300);
	collisionManager->addObjectCollider(towerSOCollider);
}

void activateTower(glm::vec2 pos) {
	glm::vec2 toTower = pos - glm::vec2(-300, 300);
	float nightDist = glm::dot(toTower, toTower);
	std::cout << "night " << nightDist << "(" << toTower.x << " " << toTower.y << ")" << endl;
	if (nightDist <= 3500) {
		TickEngine::freezeTime(0.f);
	}
	else {
		toTower = pos - glm::vec2(-300, -300);
		float morningDist = glm::dot(toTower, toTower);
		std::cout << "morning " << morningDist << "(" << toTower.x << " " << toTower.y << ")" << endl;
		if (morningDist <= 3500) {
			TickEngine::freezeTime(15.f);
		}
		else {
			toTower = pos - glm::vec2(300, -300);
			float middayDist = glm::dot(toTower, toTower);
			std::cout << "midday " << middayDist << "(" << toTower.x << " " << toTower.y << ")" << endl;
			if (middayDist <= 3500) {
				TickEngine::freezeTime(30.f);
			}
			else {
				toTower = pos - glm::vec2(300, 300);
				float sunsetDist = glm::dot(toTower, toTower);
				std::cout << "sunset " << sunsetDist << "(" << toTower.x << " " << toTower.y << ")" << endl;
				if (sunsetDist <= 3500) {
					TickEngine::freezeTime(45.f);
				}
			}
		}
	}
}