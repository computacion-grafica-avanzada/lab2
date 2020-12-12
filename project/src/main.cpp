#include <windows.h>

#include <glad/glad.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"

#include "Display.h"
#include "Character.h"
#include "MainRenderer.h"
#include "Camera.h"
#include "Shader.h"
#include "ColliderFloor.h"
#include "Collider.h"
#include "TimeFrame.h"
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
	// COLLISION TESTS
	//testFloorCollisions();
	//testSphereSphereCollisions();
	//testSphereBoxCollisions();
	//return 0;

	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}


	SDL_Window* window = NULL;
	SDL_GLContext gl_context;

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 7);

	Display display = Display(800, 800);
	gl_context = SDL_GL_CreateContext(display.getWindow());
	printf("OpenGL loaded\n");
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));
	glEnable(GL_MULTISAMPLE);

	Camera* camera = new Camera(Projection::Perspective, 45, 1.f);
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
	//characterRenderer->loadObj(BEAGLE_PATH);
	//characterRenderer->setShader(worldShader);

	Renderer* island = new Renderer(camera, false);
	//island->loadObj("../models/Landscapes/three_island2.obj");
	//island->setShader(worldShader);

	//WaterRenderer* waterRenderer = new WaterRenderer(camera, waterShader, dudv, NULL);

	AnimatedRenderable* animatedCharacter = AnimatedModelLoader::loadEntity("../models/characters/player/model.dae", "../models/characters/player/diffuse.png");
	Animation* animation = AnimationLoader::loadAnimation("../models/characters/player/model.dae");
	animatedCharacter->doAnimation(animation);

	AnimationRenderer* animationRenderer = new AnimationRenderer(camera);
	animationRenderer->load(animatedCharacter);
	animationRenderer->setShader(animationShader);

	Character* character = new Character(glm::vec3(0, 0, 0), 1.0f, NULL);
	MainRenderer::setCharacter(character);
	glm::vec3 position = character->getPosition();
	character->setPosition(glm::vec3(position.x - 200, position.y, position.z));

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
		TimeFrame::update(tex);

		animatedCharacter->update();

		// TODO delta frame and tick engine

		while (SDL_PollEvent(&sdlEvent)) {
			glm::vec3 position = character->getPosition();
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
					character->setPosition(glm::vec3(position.x + 2, position.y, position.z));
					character->setDirection(FRONT);
					break;
				case SDLK_DOWN:
					character->setPosition(glm::vec3(position.x - 2, position.y, position.z));
					character->setDirection(FRONT);
					break;
				case SDLK_LEFT:
					character->setPosition(glm::vec3(position.x + 2, position.y, position.z - 2));
					character->setDirection(LEFT);
					break;
				case SDLK_RIGHT:
					character->setPosition(glm::vec3(position.x + 2, position.y, position.z + 2));
					character->setDirection(RIGHT);
					break;
				case SDLK_c:
					/*if (character->currentPathIndex == charactersSize - 1) {
						character->currentPathIndex = 0;
					}
					else {
						character->currentPathIndex++;
					}
					characterRenderer->clearMesh();
					character->path = charactersPaths[character->currentPathIndex];
					characterRenderer->loadObj(character->path);*/
					break;
				}
				break;
			case SDL_MOUSEMOTION: // look around scene
				//cout << "SDL_MOUSEMOTION" << endl;
				break;
			}
			camera->SetPosition(glm::vec3(
				position.x - 110,
				position.y + 40,
				position.z
			));
		}
		MainRenderer::render();		// call the draw function
		display.swapBuffers();	// swap buffers
	}

	//FIN LOOP PRINCIPAL
	display.distroyWindow();
	SDL_Quit();
	return 0;
}
