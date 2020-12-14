#include "Character.h"

Character::Character(glm::vec3 position) {
	this->direction = Direction::FRONT;
	this->position = position;

	this->currentChar = 0;
	CharacterSpecs beagle = { "../models/beagle/beagle_origin.obj", 50 };
	CharacterSpecs dog = { "../models/dog/dog_origin.obj", 50 };
	this->characters = { beagle, dog };
	this->feetPosOffset = 5;
}

glm::vec3 Character::getPosition() {
	return position;
}

Direction Character::getDirection() {
	return direction;
}

float Character::getFeetPosOffset() {
	return feetPosOffset;
}

void Character::setPosition(glm::vec3 position) {
	this->position = position;

}

void Character::setDirection(Direction direction) {
	this->direction = direction;
}

void Character::setFeetPosOffset(float feetPosOffset) {
	this->feetPosOffset = feetPosOffset;
}

void Character::switchCharacter() {
	currentChar = (currentChar + 1) % characters.size();
}

float Character::currentCharacterSpeed() {
	return characters[currentChar].speed;
}

std::string Character::currentCharacterPath() {
	return characters[currentChar].path;
}

