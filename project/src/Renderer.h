#pragma once

#include "Light.h"
#include "Renderable.h"
#include "Camera.h"
#include "Renderable.h"
#include <set>

class Renderer {
	Camera* camera;
	Shader* shader;
	glm::vec4 clipPlane;
	bool clipPlaneEnabled;
	glm::vec3 averageVertix;
	glm::vec3 highestVertix;
	glm::mat4 customModel;

	bool isCharacter;
	float ra = 0;
public:
	std::set<Renderable*> renderables;
	Renderer(Camera* camera, bool isCharacter, glm::mat4 customModel);
	Renderer();
	~Renderer();

	void load(Renderable* renderable);
	void unload(Renderable* renderable);
 	void clearMesh();
	void enableClipPlane(glm::vec4 clipPlane);
	void disableClipPlane();
	void render(std::set<Light*> lights);

	void loadObj(const std::string& objFile);	// for each mesh creates a renderable and adds it to set
	glm::vec3 getAverageVertix();
	glm::vec3 getHighestVertix();

	void setShader(Shader* shader);
	Shader* getShader();

	void setCustomModel(glm::mat4 customModel);
	glm::mat4 getCustomModel();
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
