#include "TickEngine.h"

float TickEngine::time = 0.f;
float TickEngine::freeze = 0.f;
std::unordered_set<ITickable*> TickEngine::objects;

void TickEngine::load(ITickable* obj) {
	objects.insert(obj);
}
void TickEngine::unload(ITickable* obj) {
	objects.erase(obj);
}
void TickEngine::tick(Texture* time) {
	if (TickEngine::freeze > 0) {
		TickEngine::freeze -= Display::deltaTime;
	}
	else {
		TickEngine::time += Display::deltaTime;
		TickEngine::time = fmod(TickEngine::time, 60.0f);
	}
	
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << TickEngine::time;
	std::string msg = "Time " + stream.str();
	
	SDL_Color gray = { 90,90,90 };
	time->setText(msg, "../OpenSans-Regular.ttf", gray, 180);
	for (ITickable* obj : objects) {
		obj->tick(TickEngine::time);
	}
}
void TickEngine::cleanUp() {
	std::unordered_set<ITickable*> aux = objects;
	for (ITickable* obj : aux) {
		delete obj;
	}
	objects.clear();
}
void TickEngine::freezeTime(float time) {
	TickEngine::time = time;
	TickEngine::freeze = 60.f;
}