#pragma once

#include <tinyxml2.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class XMLUtils
{
public:
	/* Gets a child node with a certain name, and with a given value of a given
	attribute. Used to get a specific child when there are multiple child nodes with the same node name. */
	static tinyxml2::XMLElement* firstChildElementWithAttribute(tinyxml2::XMLElement* element, std::string childName, std::string attributeName, std::string attributeValue);
	/* Get the child nodes of this node that have a given name. */
	static std::vector<tinyxml2::XMLElement*> childrenWithName(tinyxml2::XMLElement* element, std::string name);
	static std::vector<std::string> splitText(std::string text, std::string delimiter);
	static glm::mat4 rawDataToMat4(std::vector<std::string> rawData);
};

