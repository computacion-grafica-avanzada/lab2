#include "TimeFrame.h"


float TimeFrame::lastUpdate = 0.0f;
float TimeFrame::lastFPSCheck = 0.0f;
int TimeFrame::frames = 0;

float TimeFrame::deltaTime = 0.0f;
int TimeFrame::fps = 0.0f;

void TimeFrame::update(Texture* tex) {
	float time = SDL_GetTicks() / 1000.f;
	deltaTime = time - lastUpdate;
	lastUpdate = time;

	++frames;
	if (time - lastFPSCheck >= 1.0f) {
		fps = frames / (time - lastFPSCheck);
		lastFPSCheck = time;
		frames = 0;

		std::string padding = "";
		if (fps == 0) padding = "  ";
		else if (fps < 100) padding = " ";
        std::string msg = "FPS " + padding + std::to_string(TimeFrame::fps);
        SDL_Color gray = { 90,90,90 };
        tex->setText(msg, "../OpenSans-Regular.ttf", gray, 180);
		std::cout << msg << std::endl;
	}
}