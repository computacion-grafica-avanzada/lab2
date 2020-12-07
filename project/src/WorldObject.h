#pragma once
#include "SDL.h"
#include "SDL_opengl.h"

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

using namespace std;

class WorldObject {

public:
	glm::vec3 position, size;
	WorldObject();
	WorldObject(glm::vec3 position, glm::vec3 size);
};