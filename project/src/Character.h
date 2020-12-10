#pragma once
#include "Renderer.h"

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

using namespace std;

const string BEAGLE_PATH      = "../models/beagle/beagle_origin.obj";
const string DOG_PATH         = "../models/dog/dog_origin.obj";
const string charactersPaths[] = { BEAGLE_PATH, DOG_PATH };
enum Direction { LEFT, FRONT, RIGHT };

const int charactersSize = sizeof(charactersPaths) / sizeof(charactersPaths[0]);
	
class Character {
	Direction direction;
	glm::vec3 position;
public:
	string path;
	int currentPathIndex;
	Renderer* model;
	float speed;
	Character(glm::vec3 _position, float _speed, Renderer* _model);
	Direction getDirection();
	void setDirection(Direction direction);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
};