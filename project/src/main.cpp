#include <windows.h>

#include <glad/glad.h>
#include "SDL.h"
#include "SDL_opengl.h"

#include "Model.h"
#include "MainRenderer.h"
#include "Camera.h"
#include "Shader.h"
#include "ColliderFloor.h"
#include "Collider.h"

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

	SDL_Window* window = NULL;
	SDL_GLContext gl_context;

	window = SDL_CreateWindow("Ventana", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_OPENGL);

	gl_context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(0);				// disable limit of 60fps
	printf("OpenGL loaded\n");				// Check OpenGL properties
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));

	// TODO create camera
	Camera* camera = new Camera(Projection::Perspective, 45, 1.f);
	// TODO init main renderer
	MainRenderer::init(camera);
	// TODO create game manager

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	std::vector<glm::vec4> vert = {
		glm::vec4(-500,15,-500,1),
		glm::vec4(500,15,-500,1),
		glm::vec4(500,15,500,1),
		glm::vec4(-500,15,500,1),
	};

	std::vector<glm::vec2> uvs = {
		glm::vec2(0,0),
		glm::vec2(1,0),
		glm::vec2(1,1),
		glm::vec2(0,1),
	};

	std::vector<glm::vec3> norms = {
		glm::vec3(0,1,0),
		glm::vec3(0,1,0),
		glm::vec3(0,1,0),
		glm::vec3(0,1,0),
	};

	std::vector<unsigned int> ind = { 2,1,0,3,2,0 };
	//std::vector<unsigned int> ind = { 0,1,2 };

	Mesh* mimesh = new Mesh(vert, uvs, norms, ind);

	std::vector<glm::vec4> vert2 = {
		glm::vec4(-50,50,550,1),
		glm::vec4(50,50,550,1),
		glm::vec4(50,150,550,1),
		glm::vec4(-50,150,550,1),
	};

	std::vector<glm::vec2> uvs2 = {
		glm::vec2(0,0),
		glm::vec2(1,0),
		glm::vec2(1,1),
		glm::vec2(0,1),
	};

	std::vector<glm::vec3> norms2 = {
		glm::vec3(0,1,0),
		glm::vec3(0,1,0),
		glm::vec3(0,1,0),
		glm::vec3(0,1,0),
	};

	std::vector<unsigned int> ind2 = { 0,1,2,0,2,3 };
	//std::vector<unsigned int> ind = { 0,1,2 };

	Mesh* mimesh2 = new Mesh(vert2, uvs2, norms2, ind2);

	//Renderer* sky = new Renderer(camera);
	//sky->loadObj("../models/skybox.obj");

	Texture* dudv = new Texture("../models/dudv.png");

	Renderer* piso = new Renderer(camera);
	piso->loadObj("../models/plane3.obj");
	mimesh = (*piso->renderables.begin())->getMesh();
	MainRenderer::unload(piso);

	Renderer* waves = new Renderer(camera);
	waves->loadObj("../models/beach3.obj");

	Shader* wave = new Shader("./src/shaders/simple.vert", "./src/shaders/simple.frag");
	waves->setShader(wave);
	//sky->setShader(wave);
	//MainRenderer::unload(waves);

	//Renderable* mundo = new Renderable();
	//mundo->setMesh(mimesh);

	//Renderable* pared = new Renderable();
	//pared->setMesh(mimesh2);
	//Texture* naru = new Texture("../models/Naruto.PNG");
	//pared->setTexture(naru, 1);
	//Renderer* na = new Renderer(camera);
	//waves->load(pared);

	//Texture* text = new Texture("../models/Black Clover.PNG");
	//mundo->setTexture((*waves->renderables.begin())->getTexture(), 1);
	//mundo->setTexture(text, 1);

	//Renderer* renMundo = new Renderer();
	//renMundo->load(mundo);
	//renMundo->setShader(wave);
	//MainRenderer::load(renMundo);

	WaterRenderer* waterRenderer = new WaterRenderer(camera);
	Water* agua = new Water();

	//Shader* waterShade = new Shader("./src/shaders/WaterShader.vert", "./src/shaders/WaterShader.frag");
	Shader* waterShade = new Shader("./src/shaders/water.vert", "./src/shaders/water.frag");

	agua->setMesh(mimesh);
	agua->setShader(waterShade);
	agua->setDUDV(dudv);
	waterRenderer->load(agua);

	//Model a("../models/waves.obj");

	bool running = true;	// set running to true
	SDL_Event sdlEvent;		// variable to detect SDL events
	while (running)			// the event loop
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);					// set background colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

		// TODO delta frame and tick engine

		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
				running = false;
		}

		// TODO main renderer render
		MainRenderer::render();
		//a.draw();					// call the draw function
		SDL_GL_SwapWindow(window);	// swap buffers
	}

	//FIN LOOP PRINCIPAL
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
