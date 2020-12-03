#pragma once

#include <glm/glm.hpp>

//#include "../../Tickable/ITickable.h"
#include "Mesh.h"
#include "Shader.h"
//#include "Transform.h"
#include "Texture.h"

class Water {
private:
	Mesh* mesh;
	Shader* shader;
	Texture* dudv;
	Texture* normal;
	//Transform* transform;

public:
	float moveFactor;
	Water();
	~Water();

	float textureTiling;
	float distortionStrength;
	float moveSpeed;
	float specularPower;

	void setMesh(Mesh* mesh);
	void setShader(Shader* shader);
	void setDUDV(Texture* texture);
	void setNormal(Texture* normal);

	Mesh* getMesh();
	Shader* getShader();
	Texture* getDUDV();
	Texture* getNormal();
	//Transform* getTransform();
	float getMoveFactor();

	//void Tick();

	//static Mesh* GenerateMesh(glm::vec2 size);
};