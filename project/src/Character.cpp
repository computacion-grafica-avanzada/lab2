#include "Character.h"

Character::Character(glm::vec3 _position, glm::vec3 _size, float _speed, Renderer* _model) : WorldObject(_position, _size) {
    path = BEAGLE_PATH;
    currentPathIndex = 0;
	speed = _speed;
	model = _model;
}