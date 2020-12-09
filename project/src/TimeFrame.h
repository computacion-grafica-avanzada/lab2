#pragma once
#include "Texture.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <string>

class TimeFrame {
	static float lastUpdate;
	static float lastFPSCheck;
	static int frames;

public:
	static float deltaTime;
	static int fps;
	static void update(Texture* tex);
};