#pragma once
#include "Renderer.h"
#include "WorldObject.h"

#include <glm/glm.hpp>

const string BEAGLE_PATH      = "../models/beagle/beagle.obj";
const string DOG_PATH         = "../models/dog/dog.obj";
const string charactersPaths[] = { BEAGLE_PATH, DOG_PATH };
const int charactersSize = sizeof(charactersPaths) / sizeof(charactersPaths[0]);
	
class Character : public WorldObject {
public:
	string path;
	int currentPathIndex;
	Renderer* model;
	float speed;
	Character(glm::vec3 _position, glm::vec3 _size, float _speed, Renderer* _model);
};