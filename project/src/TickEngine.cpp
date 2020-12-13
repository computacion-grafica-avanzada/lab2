#include "TickEngine.h"

std::unordered_set<ITickable*> TickEngine::objects;

void TickEngine::load(ITickable* obj) {
	objects.insert(obj);
}
void TickEngine::unload(ITickable* obj) {
	objects.erase(obj);
}
void TickEngine::tick() {
	for (ITickable* obj : objects) {
		obj->tick();
	}
}
void TickEngine::cleanUp() {
	std::unordered_set<ITickable*> aux = objects;
	for (ITickable* obj : aux) {
		delete obj;
	}
	objects.clear();
}