#pragma once
#include "Renderer.h"

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

using namespace std;

const string BEAGLE_PATH      = "../models/beagle/beagle.obj";
const string DOG_PATH         = "../models/dog/dog.obj";
const string charactersPaths[] = { BEAGLE_PATH, DOG_PATH };
enum Direction { LEFT, FRONT, RIGHT };

const int charactersSize = sizeof(charactersPaths) / sizeof(charactersPaths[0]);
	
class Character {
	Direction currentDirection;
	Direction lastDirection;
	glm::vec3 position;
public:
	string path;
	int currentPathIndex;
	Renderer* model;
	float speed;
	Character(glm::vec3 _position, float _speed, Renderer* _model);
	Direction getCurrentDirection();
	Direction getLastDirection();
	void updateDirection(Direction direction);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
};