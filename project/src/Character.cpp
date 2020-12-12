#include "Character.h"

Character::Character(glm::vec3 position) {
	this->direction = Direction::FRONT;
    this->position = position;

    this->currentChar = 0;
    CharacterSpecs beagle = { "../models/beagle/beagle_origin.obj", 200 };
    CharacterSpecs dog = { "../models/dog/dog_origin.obj", 500 };
    this->characters = { beagle, dog };
}

glm::vec3 Character::getPosition() {
    return position;
}

Direction Character::getDirection() {
    return direction;
}

void Character::setDirection(Direction direction) {
    this->direction = direction;
}

void Character::setPosition(glm::vec3 position) {
    this->position = position;
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

