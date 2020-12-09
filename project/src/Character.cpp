#include "Character.h"

Character::Character(glm::vec3 _position, float _speed, Renderer* _model) {
    path = BEAGLE_PATH;
    currentPathIndex = 0;
	speed = _speed;
	model = _model;
	currentDirection = FRONT;
	lastDirection = FRONT;	
    position = _position;
}

Direction Character::getCurrentDirection() {
    return currentDirection;
}

Direction Character::getLastDirection() {
    return lastDirection;
}

void Character::updateDirection(Direction _direction) {
    lastDirection = currentDirection;
    currentDirection = _direction;
}

glm::vec3 Character::getPosition() {
    return position;
}

void Character::setPosition(glm::vec3 _position) {
    position = _position;
}