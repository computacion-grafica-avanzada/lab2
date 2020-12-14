#pragma once

#include <unordered_set>
#include "ITickable.h"
#include "Display.h"
#include "Texture.h"
#include <iomanip>
#include <sstream>

class TickEngine {
private:
	static float time;
	static float freeze;
	static std::unordered_set<ITickable*> objects;

public:
	static void load(ITickable* obj);
	static void unload(ITickable* obj);
	static void tick(Texture* time);
	static void freezeTime(float time);
	static void cleanUp();
};