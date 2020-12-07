#include "WorldObject.h"

WorldObject::WorldObject() {
	position = glm::vec3(0.f, 0.f, 0.f);
	size = glm::vec3(1.f, 1.f, 1.f);
}

WorldObject::WorldObject(glm::vec3 _position, glm::vec3 _size) {
	position = _position;
	size = _size;
}