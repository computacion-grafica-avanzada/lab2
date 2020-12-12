#include "XMLUtils.h"

tinyxml2::XMLElement* XMLUtils::firstChildElementWithAttribute(tinyxml2::XMLElement* element, std::string childName, std::string attributeName, std::string attributeValue)
{
	for (tinyxml2::XMLElement* node = element->FirstChildElement(childName.c_str()); node; node = node->NextSiblingElement(childName.c_str()))
	{
		if (std::string(node->Attribute(attributeName.c_str())) == attributeValue)
		{
			return node;
		}
	}
}

std::vector<tinyxml2::XMLElement*> XMLUtils::childrenWithName(tinyxml2::XMLElement* element, std::string name)
{
	std::vector<tinyxml2::XMLElement*> children;

	for (tinyxml2::XMLElement* node = element->FirstChildElement(name.c_str()); node; node = node->NextSiblingElement())
	{
		if (std::string(node->Name()) == name)
		{
			children.push_back(node);
		}
	}

	return children;
}

std::vector<std::string> XMLUtils::splitText(std::string text, std::string delimiter)
{
	std::vector<std::string> res;
	std::string word;
	size_t pos = 0;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		word = text.substr(0, pos);
		res.push_back(word);
		text.erase(0, pos + 1);
	}
	if (text != "")
	{
	res.push_back(text);
	}
	return res;
}
