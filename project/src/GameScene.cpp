#include "GameScene.h"

void initIsland(Camera* camera, Shader* world) {
	initTowers(camera, world);
	initTrees(camera, world);
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

void initTrees(Camera* camera, Shader* world) {
	float height = 125.f;
	//glm::vec3 scale(200, height, 200);
	glm::vec3 scale(height);

	// SE tower
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0, 20, 0));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* tree = new Renderer(camera, false, model);
	tree->loadObj("../models/Trees/final.obj");
	tree->setShader(world);

	// SE island
	height = 140.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 10, 200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* tree2 = new Renderer(camera, false, model);
	tree2->renderables = tree->renderables;
	tree2->setShader(world);

	// NE island
	height = 155.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(300, 0, -200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(135.f), glm::vec3(0, 1, 0));
	Renderer* tree3 = new Renderer(camera, false, model);
	tree3->renderables = tree->renderables;
	tree3->setShader(world);

	height = 170.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(200, 0, -300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 1, 0));
	Renderer* tree4 = new Renderer(camera, false, model);
	tree4->renderables = tree->renderables;
	tree4->setShader(world);

	// NO island
	height = 185.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 0, -200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(225.f), glm::vec3(0, 1, 0));
	Renderer* tree5 = new Renderer(camera, false, model);
	tree5->renderables = tree->renderables;
	tree5->setShader(world);

	height = 200.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-200, 10, -300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(270.f), glm::vec3(0, 1, 0));
	Renderer* tree6 = new Renderer(camera, false, model);
	tree6->renderables = tree->renderables;
	tree6->setShader(world);

	height = 215.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-400, 30, -300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(315.f), glm::vec3(0, 1, 0));
	Renderer* tree7 = new Renderer(camera, false, model);
	tree7->renderables = tree->renderables;
	tree7->setShader(world);

	// SO island
	height = 230.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 0, 200));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(360.f), glm::vec3(0, 1, 0));
	Renderer* tree8 = new Renderer(camera, false, model);
	tree8->renderables = tree->renderables;
	tree8->setShader(world);

	height = 245.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-200, 0, 300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0));
	Renderer* tree9 = new Renderer(camera, false, model);
	tree9->renderables = tree->renderables;
	tree9->setShader(world);

	height = 260.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-400, 0, 300));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0));
	Renderer* tree10 = new Renderer(camera, false, model);
	tree10->renderables = tree->renderables;
	tree10->setShader(world);

	height = 275.f;
	model = glm::translate(glm::mat4(1.0), glm::vec3(-300, 30, 400));
	model = glm::scale(model, glm::vec3(height));
	model = glm::rotate(model, glm::radians(135.f), glm::vec3(0, 1, 0));
	Renderer* tree11 = new Renderer(camera, false, model);
	tree11->renderables = tree->renderables;
	tree11->setShader(world);
}

void initTowers(Camera* camera, Shader* world) {

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
	towerSO->load(towerBaseSO);
	towerSO->setShader(world);
}
