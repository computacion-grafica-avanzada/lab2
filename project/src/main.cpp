#include <windows.h>

#include <glad/glad.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"

#include "Display.h"
#include "Character.h"
#include "MainRenderer.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "Shader.h"
#include "ColliderFloor.h"
#include "Collider.h"
#include "GuiRenderer.h"
#include "ColladaLoader.h"
#include "AnimatedRenderable.h"
#include "Animation.h"
#include "AnimatedModelLoader.h"
#include "AnimationLoader.h"

using namespace std;

void testFloorCollisions()
{
	glm::vec3 v1, v2, v3, pos;

	v1 = glm::vec3(-0.5f, 0, 0);
	v2 = glm::vec3(0.5f, 0, 0);
	v3 = glm::vec3(0.5f, 0.69f, 0.721);

	pos = glm::vec3(0.2f, 1.0f, 0.315f);

	printf("Is point in triangle: %s", ColliderFloor::isPointInTriangle(v1, v2, v3, pos) ? "true" : "false");
	printf("\nHeight of point: %.6f", ColliderFloor::heightOfTriangleAtPos(v1, v2, v3, pos));

	pos = glm::vec3(1.0f, 1.0f, 0.315f);
	printf("\nIs point in triangle: %s", ColliderFloor::isPointInTriangle(v1, v2, v3, pos) ? "true" : "false");
}

void testSphereSphereCollisions()
{
	Collider* sphere1 = new Collider(0, 1, 0.5f);
	sphere1->pos = glm::vec3(0, 0.5f, -1);
	Collider* sphere2 = new Collider(1, 1, 0.5f);
	sphere2->pos = glm::vec3(0.5f, 0.5f, -1.5f);

	Collider::solveCollisionSphereSphere(sphere1, sphere2);

	printf("\nSphere 1 pos: (%.6f, %.6f, %.6f)", sphere1->pos.x, sphere1->pos.y, sphere1->pos.z);
	printf("\nSphere 2 pos: (%.6f, %.6f, %.6f)", sphere2->pos.x, sphere2->pos.y, sphere2->pos.z);
}

void testSphereBoxCollisions()
{
	Collider* sphere = new Collider(0, 1, 0.5f);
	sphere->pos = glm::vec3(0.15f, 0.5f, -0.5f);
	Collider* box = new Collider(1, 0, 1, 1, 1);
	box->pos = glm::vec3(-0.1f, 0.5f, 0.3f);

	Collider::solveCollisionSphereBox(sphere, box);

	printf("\nSphere pos: (%.6f, %.6f, %.6f)", sphere->pos.x, sphere->pos.y, sphere->pos.z);
	printf("\nBox pos: (%.6f, %.6f, %.6f)", box->pos.x, box->pos.y, box->pos.z);
}

int main(int argc, char* argv[]) {

	//glm::mat4 testMat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	//glm::quat testQuat = glm::quat_cast(testMat);

	//testMat = glm::transpose(testMat);
	//Quaternion* testQuat2 = Quaternion::fromMatrix(testMat);

	//glm::mat4 idMat = glm::identity<glm::mat4>();
	//idMat = glm::translate(idMat, glm::vec3(5, 5, 5));

	//glm::vec3 translateVec = idMat[3];

	// COLLISION TESTS
	//testFloorCollisions();
	//testSphereSphereCollisions();
	//testSphereBoxCollisions();
	//return 0;

	Display::init(800, 800);
	Character* character = new Character(glm::vec3(10, 10, 0));// , characterRenderer);
	Camera* camera = new Camera(character, 45, 1.f);
	MainRenderer::init(camera);

	glEnable(GL_DEPTH_TEST);
	MainRenderer::enable_culling();

	// Create shaders
	Shader* worldShader = new Shader("./src/shaders/simple.vert", "./src/shaders/simple.frag");
	Shader* animationShader = new Shader("./src/shaders/animated.vert", "./src/shaders/simple.frag");
	Shader* waterShader = new Shader("./src/shaders/water.vert", "./src/shaders/water.frag");
	Shader* textShader = new Shader("./src/shaders/text.vert", "./src/shaders/text.frag");

	Texture* dudv = new Texture("../models/dudv.png");

	//Renderer* characterRenderer = new Renderer(camera, true);
	//characterRenderer->loadObj(character->currentCharacterPath());
	//characterRenderer->setShader(worldShader);

	//WaterRenderer* waterRenderer = new WaterRenderer(camera, waterShader, dudv, NULL);

	AnimatedRenderable* animatedCharacter = AnimatedModelLoader::loadEntity("../models/characters/player/model.dae", "../models/characters/player/diffuse.png");
	Animation* animation = AnimationLoader::loadAnimation("../models/characters/player/model.dae");
	animatedCharacter->doAnimation(animation);

	AnimationRenderer* animationRenderer = new AnimationRenderer(camera);
	animationRenderer->load(animatedCharacter);
	animationRenderer->setShader(animationShader);

	//Character* character = new Character(glm::vec3(0, 0, 0));
	//characterRenderer->setShader(worldShader);
	MainRenderer::setCharacter(character);
	glm::vec3 position = character->getPosition();
	character->setPosition(glm::vec3(position.x - 200, position.y, position.z));
	Collider* characterCollider = new Collider(0, 1, 15.0f);

	Renderer* island = new Renderer(camera, false);
	//island->loadObj("../models/Landscapes/three_island2.obj");
	//island->loadObj("../models/Landscapes/floor.obj");
	//island->setShader(worldShader);

	std::set<Mesh*> floorMeshes;
	for (Renderable* renderable : island->renderables) {
		floorMeshes.insert(renderable->getMesh());
	}
	ColliderFloor* floorCollider = new ColliderFloor(floorMeshes);

	/*Renderer* boat = new Renderer(camera, false);
	boat->loadObj("../models/boat/boat3.obj");
	boat->setShader(worldShader);
	Collider* boatCollider = new Collider(2, 2, 18.0f);
	boatCollider->pos = boat->getAverageVertix();*/

	//WaterRenderer* waterRenderer = new WaterRenderer(camera, waterShader, dudv, NULL);

	CollisionManager* collisionManager = new CollisionManager(characterCollider, floorCollider);
	//collisionManager->addObjectCollider(boatCollider);

	// create Gui with FPS
	Texture* tex = new Texture();
	GuiTexture* fps = new GuiTexture();
	fps->tex = tex;
	fps->scale = glm::vec2(0.125, 0.0625);
	fps->position = glm::vec2(0.875, 0.9375);

	GuiRenderer* guiRend = new GuiRenderer(textShader);
	guiRend->load(fps);

	bool running = true;	// set running to true
	SDL_Event sdlEvent;		// variable to detect SDL events
	while (running)			// the event loop
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);					// set background colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window
		Display::update(tex);

		animatedCharacter->update();

		// TODO delta frame and tick engine
		//SDL_SetRelativeMouseMode((SDL_bool) true);
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
					//character->setPosition(glm::vec3(position.x, position.y, position.z - 2));
					character->setDirection(Direction::LEFT);
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					character->setPosition(position + glm::normalize(cross) * cameraSpeed);
					character->setDirection(Direction::RIGHT);
					break;
				case SDLK_SPACE:
					character->setPosition(position + camera->GetUp() * cameraSpeed);
					break;
				case SDLK_LSHIFT:
					character->setPosition(position - camera->GetUp() * cameraSpeed);
					break;
				case SDLK_c:
					/*character->switchCharacter();
					characterRenderer->clearMesh();
					characterRenderer->loadObj(character->currentCharacterPath());*/
					break;
				case SDLK_r:
					camera->resetCamera();
					break;
				}
				break;
			case SDL_MOUSEMOTION: // look around scene
			{
				if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					camera->setAap(sdlEvent.motion.xrel);
					camera->setPitch(sdlEvent.motion.yrel);
				}
				break;
			}
			case SDL_MOUSEWHEEL:
			{
				camera->setZoom(sdlEvent.wheel.y);
			}
			}
		}
		// characterCollider->pos = character->getPosition();
		// collisionManager->solvePlayerCollisions();
		// character->setPosition(characterCollider->pos); // correct it in case of collision
		camera->UpdateVectors();
		MainRenderer::render();		// call the draw function
		Display::swapBuffers();	// swap buffers
	}

	//FIN LOOP PRINCIPAL
	Display::destroy();
	return 0;
}
