#include "Display.h"

Display::Display(int _width, int _height) {
	width = _width;
	height = _height;

	deltaTime = 0.f; // Time between current frame and last frame
	lastFrame = 0.f; // Time of last frame
    window = SDL_CreateWindow("Ventana", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
																	width, height, SDL_WINDOW_OPENGL);
																	
	//disable limit of 60fps
	SDL_GL_SetSwapInterval(0);
}

int Display::getWidth() {
	return width;
}

int Display::getHeight() {
	return height;
}

float Display::getDelta() {
	float currentFrame = SDL_GetTicks() / 1000.f;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	return deltaTime;
}

void Display::swapBuffers() {
	SDL_GL_SwapWindow(window);
}

SDL_Window* Display::getWindow() {
	return window;
}

void Display::distroyWindow() {
	SDL_DestroyWindow(window);
}
