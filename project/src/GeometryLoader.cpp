#include "GeometryLoader.h"

void GeometryLoader::readRawData()
{
	readPositions();
	readNormals();
	readTextureCoords();
}

void GeometryLoader::readPositions()
{
	std::string positionsId = meshData->FirstChildElement("vertices")->FirstChildElement("input")->Attribute("source") + 1;
	tinyxml2::XMLElement* positionsData = XMLUtils::firstChildElementWithAttribute(meshData, "source", "id", positionsId)->FirstChildElement("float_array");
	int count = std::stoi(positionsData->Attribute("count"));
	std::vector<std::string> posData = XMLUtils::splitText(positionsData->GetText(), " ");
	for (int i = 0; i < count / 3; i++)
	{
		float x = std::stof(posData[i * 3]);
		float y = std::stof(posData[i * 3 + 1]);
		float z = std::stof(posData[i * 3 + 2]);
		glm::vec4 position(x, y, z, 1);
		position = CORRECTION * position;
		vertices.push_back(new Vertex(vertices.size(), glm::vec3(position.x, position.y, position.z), vertexWeights[vertices.size()]));
	}
}

void GeometryLoader::readNormals()
{
	std::string normalsId = XMLUtils::firstChildElementWithAttribute(meshData->FirstChildElement("polylist"), "input", "semantic", "NORMAL")->Attribute("source") + 1;
	tinyxml2::XMLElement* normalsData = XMLUtils::firstChildElementWithAttribute(meshData, "source", "id", normalsId)->FirstChildElement("float_array");
	int count = std::stoi(normalsData->Attribute("count"));
	std::vector<std::string> normData = XMLUtils::splitText(normalsData->GetText(), " ");
	for (int i = 0; i < count / 3; i++)
	{
		float x = std::stof(normData[i * 3]);
		float y = std::stof(normData[i * 3 + 1]);
		float z = std::stof(normData[i * 3 + 2]);
		glm::vec4 norm(x, y, z, 0);
		norm = CORRECTION * norm;
		normalsVector.push_back(glm::vec3(norm.x, norm.y, norm.z));
	}
}

void GeometryLoader::readTextureCoords()
{
	std::string texCoordsId = XMLUtils::firstChildElementWithAttribute(meshData->FirstChildElement("polylist"), "input", "semantic", "TEXCOORD")->Attribute("source") + 1;
	tinyxml2::XMLElement* texCoordsData = XMLUtils::firstChildElementWithAttribute(meshData, "source", "id", texCoordsId)->FirstChildElement("float_array");
	int count = std::stoi(texCoordsData->Attribute("count"));
	std::vector<std::string> texData = XMLUtils::splitText(texCoordsData->GetText(), " ");
	for (int i = 0; i < count / 2; i++)
	{
		float s = std::stof(texData[i * 2]);
		float t = std::stof(texData[i * 2 + 1]);
		texturesVector.push_back(glm::vec2(s, t));
	}
}

void GeometryLoader::assembleVertices()
{
	tinyxml2::XMLElement* poly = meshData->FirstChildElement("polylist");
	int typeCount = XMLUtils::childrenWithName(poly, "input").size();
	std::vector<std::string> indexData = XMLUtils::splitText(poly->FirstChildElement("p")->GetText(), " ");
	for (int i = 0; i < indexData.size() / typeCount; i++)
	{
		int positionIndex = std::stoi(indexData[i * typeCount]);
		int normalIndex = std::stoi(indexData[i * typeCount + 1]);
		int texCoordIndex = std::stoi(indexData[i * typeCount + 2]);
		processVertex(positionIndex, normalIndex, texCoordIndex);
	}
}

Vertex* GeometryLoader::processVertex(int posIndex, int normIndex, int texIndex)
{
	Vertex* currentVertex = vertices[posIndex];
	if (!currentVertex->isSet())
	{
		currentVertex->setTextureIndex(texIndex);
		currentVertex->setNormalIndex(normIndex);
		indicesVector.push_back(posIndex);
		return currentVertex;
	}
	else
	{
		return dealWithAlreadyProcessedVertex(currentVertex, texIndex, normIndex);
	}
}

float GeometryLoader::convertDataToVectors()
{
	float furthestPoint = 0;
	std::vector< glm::vec2> auxTexturesVector;
	std::vector< glm::vec3> auxNormalsVector;

	for (int i = 0; i < vertices.size(); i++)
	{
		Vertex* currentVertex = vertices[i];
		if (currentVertex->getLength() > furthestPoint)
		{
			furthestPoint = currentVertex->getLength();
		}
		glm::vec3 position = currentVertex->getPosition();
		glm::vec2 textureCoord = texturesVector[currentVertex->getTextureIndex()];
		glm::vec3 normalVector = normalsVector[currentVertex->getNormalIndex()];
		verticesVector.push_back(glm::vec4(position, 1.0f));
		auxTexturesVector.push_back(textureCoord);
		auxNormalsVector.push_back(normalVector);
		VertexSkinData* weights = currentVertex->getWeightsData();
		glm::uvec3 jointIds(weights->jointIds[0], weights->jointIds[1], weights->jointIds[2]);
		jointIdsVector.push_back(jointIds);
		glm::vec3 jointsWeights(weights->weights[0], weights->weights[1], weights->weights[2]);
		weightsVector.push_back(jointsWeights);
	}
	texturesVector = auxTexturesVector;
	normalsVector = auxNormalsVector;

	return furthestPoint;
}

Vertex* GeometryLoader::dealWithAlreadyProcessedVertex(Vertex* previousVertex, int newTextureIndex, int newNormalIndex)
{
	if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex))
	{
		indicesVector.push_back(previousVertex->getIndex());
		return previousVertex;
	}
	else
	{
		Vertex* anotherVertex = previousVertex->getDuplicateVertex();
		if (anotherVertex)
		{
			return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex);
		}
		else
		{
			Vertex* duplicateVertex = new Vertex(vertices.size(), previousVertex->getPosition(), previousVertex->getWeightsData());
			duplicateVertex->setTextureIndex(newTextureIndex);
			duplicateVertex->setNormalIndex(newNormalIndex);
			previousVertex->setDuplicateVertex(duplicateVertex);
			vertices.push_back(duplicateVertex);
			indicesVector.push_back(duplicateVertex->getIndex());
			return duplicateVertex;
		}
	}
}

void GeometryLoader::clearVectors()
{
	this->verticesVector.clear();
	this->texturesVector.clear();
	this->normalsVector.clear();
	this->jointIdsVector.clear();
	this->weightsVector.clear();
}

void GeometryLoader::removeUnusedVertices()
{
	for (Vertex* vertex : vertices)
	{
		vertex->averageTangents();
		if (!vertex->isSet())
		{
			vertex->setTextureIndex(0);
			vertex->setNormalIndex(0);
		}
	}
}

GeometryLoader::GeometryLoader(tinyxml2::XMLElement* geometryNode, std::vector<VertexSkinData*> vertexWeights)
{
	this->vertexWeights = vertexWeights;
	this->meshData = geometryNode->FirstChildElement("geometry")->FirstChildElement("mesh");
}

MeshData* GeometryLoader::extractModelData()
{
	clearVectors();
	readRawData();
	assembleVertices();
	removeUnusedVertices();
	convertDataToVectors();
	return new MeshData(verticesVector, texturesVector, normalsVector, jointIdsVector, weightsVector, indicesVector, vertices.size());
}