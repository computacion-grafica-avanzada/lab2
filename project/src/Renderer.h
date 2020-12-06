#pragma once

//#include "Camera.h"
#include "Renderable.h"
#include "Camera.h"
#include <set>

class Renderer {
	Camera* camera;
	Shader* shader;
	glm::vec4 clipPlane;
	bool clipPlaneEnabled;

	float ra = 0;
public:
	std::set<Renderable*> renderables;
	Renderer(Camera* camera);
	Renderer();
	~Renderer();

	void load(Renderable* renderable);
	void unload(Renderable* renderable);

	void enableClipPlane(glm::vec4 clipPlane);
	void disableClipPlane();
	void render();

	void loadObj(const std::string& objFile);	// for each mesh creates a renderable and adds it to set
	
	void setShader(Shader* shader);
	Shader* getShader();
};

struct TriangleMesh {
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<unsigned int> indices;

	// material data:
	glm::vec3 diffuse;          // diffuse coefficient
	glm::vec3 specular;         // specular coefficient
	glm::vec3 transmission;     // transmission coefficient
	float ior;              // index of refraction
	float phong;            // phong exponent
	int   diffuseTextureID{ -1 };
};