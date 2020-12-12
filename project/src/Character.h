#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

struct CharacterSpecs {
	std::string path;
	float speed;
};

enum class Direction { LEFT, RIGHT, FRONT, BACK, NONE };
	
class Character {
	glm::vec3 position;
	size_t currentChar;
	std::vector<CharacterSpecs> characters;
	Direction direction;
public:
	Character(glm::vec3 position);
	
	glm::vec3 getPosition();
	Direction getDirection();

	void setPosition(glm::vec3 position);
	void setDirection(Direction direction);

	void switchCharacter();
	float currentCharacterSpeed();
	std::string currentCharacterPath();
};