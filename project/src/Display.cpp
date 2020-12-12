#include "Display.h"

int Display::width;
int Display::height;
int Display::frames = 0;
float Display::lastUpdate = 0.0f;
float Display::lastFPSCheck = 0.0f;

int Display::fps = 0.0f;
float Display::deltaTime = 0.0f;

SDL_Window* Display::window = NULL;
SDL_GLContext Display::gl_context;

void Display::init(int width, int height) {
	Display::width = width;
	Display::height = height;

	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (TTF_Init() == -1) {
		printf("Failed to initialize TTF: %s\n", TTF_GetError());
		exit(2);
	}

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    Display::window = SDL_CreateWindow(
		"Ventana", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED,
		width, 
		height, 
		SDL_WINDOW_OPENGL
	);

	Display::gl_context = SDL_GL_CreateContext(Display::window);

	SDL_GL_SetSwapInterval(0);				// disable limit of 60fps
	printf("OpenGL loaded\n");				// Check OpenGL properties
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));
	glEnable(GL_MULTISAMPLE);
}

void Display::update(Texture* tex) {
	float time = SDL_GetTicks() / 1000.f;
	deltaTime = time - lastUpdate;
	lastUpdate = time;

	++frames;
	if (time - lastFPSCheck >= 1.0f) {
		fps = frames / (time - lastFPSCheck);
		lastFPSCheck = time;
		frames = 0;

		std::string msg = "FPS " + std::to_string(Display::fps);
		SDL_Color gray = { 90,90,90 };
		tex->setText(msg, "../OpenSans-Regular.ttf", gray, 180);
		//std::cout << msg << std::endl;
	}
}

void Display::swapBuffers() {
	SDL_GL_SwapWindow(Display::window);
}

void Display::destroy() {
	SDL_GL_DeleteContext(Display::gl_context);
	SDL_DestroyWindow(Display::window);
	SDL_Quit();
}
