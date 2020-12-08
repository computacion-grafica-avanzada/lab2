#pragma once
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>

using namespace std;

class Display {
	int width, height;
	float deltaTime, lastFrame;
    SDL_Window *window;

public:
	Display(int width, int height);

	int getWidth();
	int getHeight();
	float getDelta();
    SDL_Window* getWindow();
	void swapBuffers();
	void distroyWindow();
};