#include <windows.h>

#include <glad/glad.h>
#include "SDL.h"
#include "SDL_opengl.h"

#include "Display.h"
#include "Character.h"
#include "MainRenderer.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "Shader.h"
#include "ColliderFloor.h"
#include "Collider.h"
#include "GuiRenderer.h"
#include "TickEngine.h"
#include "GameScene.h"
#include "ColliderFloor.h"

using namespace std;

void testFloorCollisions()
{
	glm::vec3 v1, v2, v3, pos;

	v1 = glm::vec3(-0.5f, 0, 0);
	v2 = glm::vec3(0.5f, 0, 0);
	v3 = glm::vec3(0.5f, 0.69f, 0.721);

	pos = glm::vec3(0.2f, 1.0f, 0.315f);

	//printf("Is point in triangle: %s", ColliderFloor::isPointInTriangle(v1, v2, v3, pos) ? "true" : "false");
	//printf("\nHeight of point: %.6f", ColliderFloor::heightOfTriangleAtPos(v1, v2, v3, pos));

	pos = glm::vec3(1.0f, 1.0f, 0.315f);
	//printf("\nIs point in triangle: %s", ColliderFloor::isPointInTriangle(v1, v2, v3, pos) ? "true" : "false");
}

void testSphereSphereCollisions()
{
	Collider* sphere1 = new Collider(0, 1, 0.5f);
	sphere1->pos = glm::vec3(0, 0.5f, -1);
	Collider* sphere2 = new Collider(1, 1, 0.5f);
	sphere2->pos = glm::vec3(0.5f, 0.5f, -1.5f);

	Collider::solveCollisionSphereSphere(sphere1, sphere2);

	//printf("\nSphere 1 pos: (%.6f, %.6f, %.6f)", sphere1->pos.x, sphere1->pos.y, sphere1->pos.z);
	//printf("\nSphere 2 pos: (%.6f, %.6f, %.6f)", sphere2->pos.x, sphere2->pos.y, sphere2->pos.z);
}

void testSphereBoxCollisions()
{
	Collider* sphere = new Collider(0, 1, 0.5f);
	sphere->pos = glm::vec3(0.15f, 0.5f, -0.5f);
	Collider* box = new Collider(1, 0, 1, 1, 1);
	box->pos = glm::vec3(-0.1f, 0.5f, 0.3f);

	Collider::solveCollisionSphereBox(sphere, box);

	//printf("\nSphere pos: (%.6f, %.6f, %.6f)", sphere->pos.x, sphere->pos.y, sphere->pos.z);
	//printf("\nBox pos: (%.6f, %.6f, %.6f)", box->pos.x, box->pos.y, box->pos.z);
}

void testSphereCapsuleCollisions()
{
	Collider* sphere = new Collider(0, 1, 0.5f);
	sphere->pos = glm::vec3(-0.8f, 5.8f, 0);
	Collider* capsule = new Collider(1, 0, 0.5f, 10);
	capsule->pos = glm::vec3(0, 0, 0);

	Collider::solveCollisionSphereCapsule(sphere, capsule);

	//printf("\nSphere pos: (%.6f, %.6f, %.6f)", sphere->pos.x, sphere->pos.y, sphere->pos.z);
	//printf("\nCapsule pos: (%.6f, %.6f, %.6f)", capsule->pos.x, capsule->pos.y, capsule->pos.z);
}

int main(int argc, char* argv[]) {
	// COLLISION TESTS
	//testFloorCollisions();
	//testSphereSphereCollisions();
	//testSphereBoxCollisions();
	//testSphereCapsuleCollisions();
	//return 0;

	Display::init(800, 800);
	Character* character = new Character(glm::vec3(0, 60, 5));
	Camera* camera = new Camera(character, 45, 1.f);
	MainRenderer::init(camera);

	glEnable(GL_DEPTH_TEST);
	MainRenderer::enable_culling();

	// Create shaders
	Shader* worldShader = new Shader("../shaders/simple.vert", "../shaders/simple.frag");
	Shader* waterShader = new Shader("../shaders/water.vert", "../shaders/water.frag");
	Shader* textShader = new Shader("../shaders/text.vert", "../shaders/text.frag");


	Renderer* characterRenderer = new Renderer(camera, true, glm::mat4(1.0));
	characterRenderer->loadObj(character->currentCharacterPath());

	characterRenderer->setShader(worldShader);
	MainRenderer::setCharacter(character);
	Collider* characterCollider = new Collider(0, 1, 40.0f);

	//Renderer* island = new Renderer(camera, false);
	////island->loadObj("../models/Landscapes/three_island2.obj");
	//island->loadObj("../models/Landscapes/floor.obj");
	//island->setShader(worldShader);

	Renderer* island2 = new Renderer(camera, false, glm::mat4(1.0));
	//island->loadObj("../models/Landscapes/three_island2.obj");
	island2->loadObj("../models/Landscapes/island_low_nice.obj");
	island2->setShader(worldShader);

	std::set<Mesh*> floorMeshes;
	for (Renderable* renderable : island2->renderables) {
		floorMeshes.insert(renderable->getMesh());
	}
	ColliderFloor* floorCollider = new ColliderFloor(floorMeshes);

	glm::mat4 fishModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-80, -5, 100));
	Renderer* fish = new Renderer(camera, false, fishModelMatrix);
	fish->loadObj("../models/fish/big_fish.obj");
	fish->setShader(worldShader);

	glm::mat4 fishModelMatrix2 = glm::translate(glm::mat4(1.0), glm::vec3(120, -5, -100));
	Renderer* fish2 = new Renderer(camera, false, fishModelMatrix);
	fish2->loadObj("../models/fish/big_fish.obj");
	fish2->setShader(worldShader);

	ColliderFloor* colliderFloor = new ColliderFloor(floorMeshes);

	CollisionManager* collisionManager = new CollisionManager(characterCollider, colliderFloor);

	initIsland(camera, worldShader, collisionManager);

	Texture* dudv = new Texture("../models/waterDUDV.png");
	Texture* normal = new Texture("../models/normal.png");
	Light* light = new Light(glm::vec3(550), glm::vec3(1, 1, 1));
	WaterRenderer* waterRenderer = new WaterRenderer(camera, waterShader, dudv, normal);

	// create Gui with FPS
	Texture* tex = new Texture();
	GuiTexture* fps = new GuiTexture();
	fps->tex = tex;
	fps->scale = glm::vec2(0.125, 0.0625);
	fps->position = glm::vec2(0.875, 0.9375);

	Texture* tex2 = new Texture();
	GuiTexture* time = new GuiTexture();
	time->tex = tex2;
	time->scale = glm::vec2(0.125, 0.0625);
	time->position = glm::vec2(0.875, 0.8125);

	Texture* texMenu = new Texture();
	GuiTexture* menu = new GuiTexture();
	menu->tex = texMenu;
	menu->scale = glm::vec2(0.6, 0.0625);
	menu->position = glm::vec2(0, 0.0625);

	Texture* texMenu2 = new Texture();
	GuiTexture* menu2 = new GuiTexture();
	menu2->tex = texMenu2;
	menu2->scale = glm::vec2(0.6, 0.0625);
	menu2->position = glm::vec2(0, -0.0625);

	SDL_Color black = { 0,0,0 };
	texMenu->setText("Go near the towers and", "../OpenSans-Regular.ttf", black, 180);
	texMenu2->setText("press P to stop time", "../OpenSans-Regular.ttf", black, 180);

	GuiRenderer* guiRend = new GuiRenderer(textShader);
	guiRend->load(fps);
	guiRend->load(time);

	bool showMenu = false;
	bool running = true;	// set running to true
	bool flyMode = false;
	int count = 0;
	SDL_Event sdlEvent;		// variable to detect SDL events
	while (running)			// the event loop
	{
		//glClearColor(1.0, 1.0, 1.0, 1.0);						// set background colour
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear window
		Display::update(tex);
		TickEngine::tick(tex2);
		if (count == 4) {
			fishModelMatrix = glm::rotate(fishModelMatrix, glm::radians(0.5f), glm::vec3(0, 1, 0));
			fish->setCustomModel(fishModelMatrix);
			fishModelMatrix2 = glm::rotate(fishModelMatrix2, glm::radians(0.8f), glm::vec3(0, 1, 0));
			fish2->setCustomModel(fishModelMatrix2);
			count = 0;
		}
		count++;
		float cameraSpeed = character->currentCharacterSpeed() * Display::deltaTime;
		while (SDL_PollEvent(&sdlEvent)) {
			glm::vec3 position = character->getPosition();
			glm::vec3 cross = glm::cross(camera->GetFront(), camera->GetUp());
			switch (sdlEvent.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (sdlEvent.key.keysym.sym) {
				case SDLK_q:
					running = false;
					break;
				case SDLK_UP:
				case SDLK_w:
					character->setPosition(position + camera->GetFront() * cameraSpeed);
					character->setDirection(Direction::FRONT);
					break;
				case SDLK_DOWN:
				case SDLK_s:
					character->setPosition(position - camera->GetFront() * cameraSpeed);
					character->setDirection(Direction::BACK);
					break;
				case SDLK_LEFT:
				case SDLK_a:
					character->setPosition(position - glm::normalize(cross) * cameraSpeed);
					character->setDirection(Direction::LEFT);
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					character->setPosition(position + glm::normalize(cross) * cameraSpeed);
					character->setDirection(Direction::RIGHT);
					break;
				case SDLK_SPACE:
					character->setPosition(position + camera->GetUp() * cameraSpeed);
					flyMode = true;
					break;
				case SDLK_LSHIFT:
					character->setPosition(position - camera->GetUp() * cameraSpeed);
					flyMode = true;
					break;
				case SDLK_LCTRL:
					flyMode = false;
					break;
				case SDLK_c:
					character->switchCharacter();
					characterRenderer->clearMesh();
					characterRenderer->loadObj(character->currentCharacterPath());
					break;
				case SDLK_r:
					camera->resetCamera();
					break;
				case SDLK_l:
					MainRenderer::toggleLod();
					break;
				case SDLK_p:
					glm::vec2 pos(character->getPosition().x, character->getPosition().z);
					activateTower(pos);
					break;
				case SDLK_m:
					if (!showMenu) {
						guiRend->load(menu);
						guiRend->load(menu2);
						showMenu = true;
					}
					else {
						guiRend->unload(menu);
						guiRend->unload(menu2);
						showMenu = false;
					}

					break;
				}
				break;
			case SDL_MOUSEMOTION: // look around scene
			{
				if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					camera->setAap(-sdlEvent.motion.xrel);
					camera->updatePitch(sdlEvent.motion.yrel);
				}
				break;
			}
			case SDL_MOUSEWHEEL:
			{
				camera->setZoom(sdlEvent.wheel.y);
			}
			}
		}
		characterCollider->pos = character->getPosition();
		collisionManager->solvePlayerCollisions(flyMode);
		character->setPosition(characterCollider->pos); // correct it in case of collision
		camera->UpdateVectors();
		MainRenderer::render();		// call the draw function
		Display::swapBuffers();		// swap buffers
	}

	//FIN LOOP PRINCIPAL
	Display::destroy();
	return 0;
}
