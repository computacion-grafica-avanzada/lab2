#pragma once
#include <glad/glad.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "Texture.h"
#include <iostream>

using namespace std;

class Display {
	static int width;
	static int height;

	static int frames;
	static float lastUpdate;
	static float lastFPSCheck;
	
	static SDL_Window* window;
	static SDL_GLContext gl_context;

public:
	static int fps;
	static float deltaTime;
	
	static void init(int width, int height);
	static void update(Texture* tex);
	static void swapBuffers();
	static void destroy();
};