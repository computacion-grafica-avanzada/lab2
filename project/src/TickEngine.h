#pragma once

#include <unordered_set>
#include "ITickable.h"

class TickEngine {
private:
	static std::unordered_set<ITickable*> objects;

public:
	static void load(ITickable* obj);
	static void unload(ITickable* obj);
	static void tick();
	static void cleanUp();
};