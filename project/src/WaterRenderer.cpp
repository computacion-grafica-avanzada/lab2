#include "WaterRenderer.h"
#include "MainRenderer.h"

WaterRenderer::WaterRenderer(Camera* camera) {
	this->camera = camera;
	MainRenderer::load(this);
}

WaterRenderer::~WaterRenderer() {
	MainRenderer::unload(this);
}

void WaterRenderer::load(Water* water) {
	Shader* shader = water->getShader();
	shader->bind();
	shader->setUniform1i("reflectionSampler", 0);
	shader->setUniform1i("refractionSampler", 1);
	shader->setUniform1i("dudvSampler", 2);
	//shader->setUniform1i("normalSampler", 3);
	//shader->setUniform1i("depthSampler", 4);
	shader->unbind();
	waters.insert(water);
}

void WaterRenderer::unload(Water* water) {
	waters.erase(water);
}

float rae = 0;

void WaterRenderer::render(WaterFrameBuffer* waterFrameBuffer) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (Water* water : waters) {
		Shader* shader = water->getShader();
		VertexArray* vArray = water->getMesh()->getVertexArray();
		IndexBuffer* iBuffer = water->getMesh()->getIndexBuffer();

		shader->bind();
		vArray->bind();
		iBuffer->bind();

		water->moveFactor += water->moveSpeed * 0.07;
		water->moveFactor = fmod(water->moveFactor, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, waterFrameBuffer->getReflectionTexture());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, waterFrameBuffer->getRefractionTexture());

		water->getDUDV()->bind(2);

		//water->getDUDV()->bind(2);
		//water->getNormal()->bind(3);
		//glActiveTexture(GL_TEXTURE4);
		//glBindTexture(GL_TEXTURE_2D, waterFrameBuffer->getRefractionDepthTexture());

		//shader->SetUniform1f("near", camera->GetNearClip());
		//shader->SetUniform1f("far", camera->GetFarClip());
		//shader->SetUniform3f("lightPosition", Light::position);
		//shader->SetUniform3f("lightColor", Light::color);
		//shader->SetUniform3f("cameraPosition", camera->GetPosition());
		shader->setUniform1f("moveFactor", water->getMoveFactor());
		//shader->SetUniform1f("textureTiling", water->textureTiling);
		//shader->SetUniform1f("distorsionStrength", water->distorsionStrength);
		//shader->SetUniform1f("specularPower", water->specularPower);

		glm::mat4 projection = glm::perspective(45.0f, 1.f, 0.1f, 2000.f);

		// Create view matrix for the camera
		//glm::mat4 view = glm::lookAt(glm::vec3(-1500, 100, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		//glm::mat4 view = glm::lookAt(glm::vec3(-500, 100, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		rae += 0.0001; //for camera rotation

		glm::mat4 view = camera->GetViewMatrix();
		//view = glm::rotate(view, rae, glm::vec3(1.0f, 0.0f, 0.0f));

		// Create model matrix for model transformations
		glm::mat4 model(1.0);

		shader->setUniform1f("textureTiling", 1);
		shader->setUniformMatrix4fv("projection", camera->GetProjectionMatrix());
		//shader->setUniformMatrix4fv("projection", projection);
		shader->setUniformMatrix4fv("view", view);
		shader->setUniformMatrix4fv("model", model);

		//shader->SetUniformMatrix4fv("gCamera", camera->GetViewMatrix());
		//shader->SetUniformMatrix4fv("gWorld", water->GetTransform()->GetMatrix());

		glDrawElements(GL_TRIANGLES, iBuffer->getCount(), GL_UNSIGNED_INT, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);

		water->getDUDV()->unbind();
		//water->getNormal()->bind(3);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);

		iBuffer->unbind();
		vArray->unbind();
		shader->unbind();
	}

	glDisable(GL_BLEND);
}