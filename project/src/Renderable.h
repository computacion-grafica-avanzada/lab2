#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
//#include "Transform.h"

class Renderable {
private:
	Mesh* mesh;
	//Transform* transform;
	Texture* texture;
	float textureTiling;

public:
	Renderable();
	~Renderable();

	void setMesh(Mesh* mesh);
	void setTexture(Texture* texture, float tiling);

	Mesh* getMesh();
	Texture* getTexture();
	float getTextureTiling();
	//Transform* getTransform();
};
