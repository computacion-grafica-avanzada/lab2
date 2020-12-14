#include "WaterRenderer.h"
#include "MainRenderer.h"

WaterRenderer::WaterRenderer(Camera* camera, Shader* shader, Texture* dudv, Texture* normal) {
	this->camera = camera;

	this->shader = shader;
	this->shader->bind();
	this->shader->setUniform1i("reflectionSampler", 0);
	this->shader->setUniform1i("refractionSampler", 1);
	this->shader->setUniform1i("dudvSampler", 2);
	this->shader->setUniform1i("normalSampler", 3);
	this->shader->setUniform1i("depthSampler", 4);
	this->shader->unbind();

	this->dudv = dudv;
	this->normal = normal;

	std::vector<glm::vec2> vertices = {
		glm::vec2(-1, 1),
		glm::vec2(-1, -1),
		glm::vec2(1, 1),
		glm::vec2(1, -1),
	};

	Buffer* vertexBuffer = new Buffer(vertices);
	vertexArray = new VertexArray();
	vertexArray->addBuffer(vertexBuffer, 0);

	moveFactor = 0;
	textureTiling = 1;
	moveSpeed = 1.0f / 40.0f;
	distortionStrength = 0.04f;
	specularPower = 20.0f;

	height = 4.f;
	scale = glm::vec2(7341, 7276);

	MainRenderer::load(this);
}

WaterRenderer::~WaterRenderer() {
	delete vertexArray;
	MainRenderer::unload(this);
}

void WaterRenderer::tick(float time) {
	moveFactor += moveSpeed * Display::deltaTime;
	moveFactor = fmod(moveFactor, 1.0f);
}

void WaterRenderer::render(std::set<Light*> lights, WaterFrameBuffer* waterFrameBuffer) {
	MainRenderer::disable_culling();
	shader->bind();
	vertexArray->bind();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, waterFrameBuffer->getReflectionTexture());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, waterFrameBuffer->getRefractionTexture());

	dudv->bind(2);
	normal->bind(3);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, waterFrameBuffer->getRefractionDepthTexture());

	shader->setUniform1f("near", camera->GetNearClip());
	shader->setUniform1f("far", camera->GetFarClip());
	
	Light* light = *lights.begin();
	shader->setUniform3f("lightPosition", light->getPosition());
	shader->setUniform3f("lightColor", light->getColor());

	shader->setUniform3f("cameraPosition", camera->GetPosition());
	shader->setUniform1f("moveFactor", moveFactor);
	//shader->SetUniform1f("textureTiling", water->textureTiling);
	//shader->SetUniform1f("distorsionStrength", water->distorsionStrength);
	//shader->SetUniform1f("specularPower", water->specularPower);

	// Create model matrix for model transformations
	glm::mat4 model(1.0);
	model = glm::translate(model, glm::vec3(0, height, 0));
	model = glm::scale(model, glm::vec3(scale.x, 0, scale.y));

	shader->setUniform1f("textureTiling", 1);
	shader->setUniformMatrix4fv("projection", camera->GetProjectionMatrix());
	shader->setUniformMatrix4fv("view", camera->GetViewMatrix());
	shader->setUniformMatrix4fv("model", model);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	dudv->unbind();
	normal->unbind();
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);
	vertexArray->unbind();
	shader->unbind();
	MainRenderer::enable_culling();
}
