#include "ITickable.h"
#include "TickEngine.h"

ITickable::ITickable() {
	TickEngine::load(this);
}
ITickable::~ITickable() {
	TickEngine::unload(this);
}