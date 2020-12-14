#include "SkyboxRenderer.h"

SkyboxRenderer::SkyboxRenderer(Camera* camera) {
	this->shader = new Shader("./src/shaders/skybox.vert", "./src/shaders/skybox.frag");
	this->camera = camera;
	
	this->clipPlane = glm::vec4(0, -1, 0, 100000);
	this->clipPlaneEnabled = false;

	this->time = 15.f;
	this->start = glm::vec3(0.529, 0.808, 0.922);
	this->end = glm::vec3(0.141, 0.643, 0.847);
	this->blendFactor = 0.f;

	float size = 1000.f;
	std::vector<glm::vec3> vertices = {
		glm::vec3(-size,  size, -size),
		glm::vec3(-size, -size, -size),
		glm::vec3( size, -size, -size),
		glm::vec3( size, -size, -size),
		glm::vec3( size,  size, -size),
		glm::vec3(-size,  size, -size),

		glm::vec3(-size, -size,  size),
		glm::vec3(-size, -size, -size),
		glm::vec3(-size,  size, -size),
		glm::vec3(-size,  size, -size),
		glm::vec3(-size,  size,  size),
		glm::vec3(-size, -size,  size),

		glm::vec3( size, -size, -size),
		glm::vec3( size, -size,  size),
		glm::vec3( size,  size,  size),
		glm::vec3( size,  size,  size),
		glm::vec3( size,  size, -size),
		glm::vec3( size, -size, -size),

		glm::vec3(-size, -size,  size),
		glm::vec3(-size,  size,  size),
		glm::vec3( size,  size,  size),
		glm::vec3( size,  size,  size),
		glm::vec3( size, -size,  size),
		glm::vec3(-size, -size,  size),

		glm::vec3(-size,  size, -size),
		glm::vec3( size,  size, -size),
		glm::vec3( size,  size,  size),
		glm::vec3( size,  size,  size),
		glm::vec3(-size,  size,  size),
		glm::vec3(-size,  size, -size),

		glm::vec3(-size, -size, -size),
		glm::vec3(-size, -size,  size),
		glm::vec3( size, -size, -size),
		glm::vec3( size, -size, -size),
		glm::vec3(-size, -size,  size),
		glm::vec3( size, -size,  size),
	};

	Buffer* vertexBuffer = new Buffer(vertices);
	vertexArray = new VertexArray();
	vertexArray->addBuffer(vertexBuffer, 0);
	//  "../models/Skybox/right",
	//	"../models/Skybox/left",
	//	"../models/Skybox/top",
	//	"../models/Skybox/bottom",
	//	"../models/Skybox/back",
	//	"../models/Skybox/front",
	std::vector<std::string> filenames = { 
		"../models/Skybox/lake2_rt.jpg", 
		"../models/Skybox/lake2_lf.jpg", 
		"../models/Skybox/lake2_up.jpg", 
		"../models/Skybox/lake2_dn.jpg", 
		"../models/Skybox/lake2_bk.jpg", 
		"../models/Skybox/lake2_ft.jpg",
	};
	cubeMap = new Texture(filenames);
}

SkyboxRenderer::~SkyboxRenderer() {
	delete vertexArray;
}

void SkyboxRenderer::enableClipPlane(glm::vec4 clipPlane) {
	this->clipPlane = clipPlane;
	this->clipPlaneEnabled = true;
}

void SkyboxRenderer::disableClipPlane() {
	this->clipPlane = glm::vec4(0, -1, 0, 100000);
	this->clipPlaneEnabled = false;
}

void SkyboxRenderer::render() {
	shader->bind();
	cubeMap->bind();
	vertexArray->bind();

	glm::mat4 no_translation = camera->GetViewMatrix();
	no_translation[3] = glm::vec4(0, 0, 0, 1);

	glm::mat4 model(1.0);

	shader->setUniform1f("blendFactor", blendFactor);
	shader->setUniform3f("skyColorStart", start);
	shader->setUniform3f("skyColorEnd", end);
	shader->setUniform4f("clipPlane", clipPlane);
	shader->setUniformMatrix4fv("projection", camera->GetProjectionMatrix());
	shader->setUniformMatrix4fv("view", no_translation);
	shader->setUniformMatrix4fv("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	vertexArray->unbind();
	cubeMap->unbind();
	shader->unbind();
}

void SkyboxRenderer::tick() {
	time += Display::deltaTime;
	time = fmod(time, 60.0f);

	// one day is one minute
	if (time >= 0 && time < 15) {
		start = glm::vec3(0);
		end = glm::vec3(0.529, 0.808, 0.922);
		blendFactor = (time - 0) / 15;
	} 
	else if (time >= 15 && time < 30) {
		start = glm::vec3(0.529, 0.808, 0.922);
		end = glm::vec3(0.141, 0.643, 0.847);
		blendFactor = (time - 15) / 15;
	} 
	else if (time >= 30 && time < 45) {
		start = glm::vec3(0.141, 0.643, 0.847);
		end = glm::vec3(0.992, 0.369, 0.325);
		blendFactor = (time - 30) / 15;
	} 
	else {
		start = glm::vec3(0.992, 0.369, 0.325);
		end = glm::vec3(0);
		blendFactor = (time - 45) / 15;
	}
}

glm::vec3 SkyboxRenderer::getSkyColor() {
	return glm::mix(start, end, blendFactor);
}


// noche - 00:00 -> negro
// manana - 06:00 -> celeste
// mediodia - 12:00 -> azul
// tarde - 18:00 -> naranja-rojo