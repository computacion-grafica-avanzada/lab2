#include "Character.h"

Character::Character(glm::vec3 _position, float _speed, Renderer* _model) {
    path = BEAGLE_PATH;
    currentPathIndex = 0;
	speed = _speed;
	model = _model;
	direction = FRONT;
    position = _position;
}

Direction Character::getDirection() {
    return direction;
}

void Character::setDirection(Direction _direction) {
    direction = _direction;
}

glm::vec3 Character::getPosition() {
    return position;
}

void Character::setPosition(glm::vec3 _position) {
    position = _position;
}