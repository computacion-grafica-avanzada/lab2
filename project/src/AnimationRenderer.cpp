#include "AnimationRenderer.h"
#include "MainRenderer.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

AnimationRenderer::AnimationRenderer(Camera* camera) {
	this->camera = camera;
	//this->clipPlaneEnabled = false;
	MainRenderer::load(this);
}

AnimationRenderer::~AnimationRenderer() {
	renderables.clear();
	MainRenderer::unload(this);
}

void AnimationRenderer::load(Renderable* renderable) {
	renderables.insert(renderable);
}

void AnimationRenderer::unload(Renderable* renderable) {
	renderables.erase(renderable);
}

//void AnimationRenderer::enableClipPlane(glm::vec4 clipPlane) {
//	this->clipPlane = clipPlane;
//	this->clipPlaneEnabled = true;
//}
//
//void AnimationRenderer::disableClipPlane() {
//	this->clipPlane = glm::vec4(0, -1, 0, 100000);
//	this->clipPlaneEnabled = false;
//}

void AnimationRenderer::render() {

	//(clipPlaneEnabled) ? glEnable(GL_CLIP_DISTANCE0) : glDisable(GL_CLIP_DISTANCE0);

	for (Renderable* renderable : renderables) {
		Shader* shader = getShader();
		Texture* texture = renderable->getTexture();
		VertexArray* vArray = renderable->getMesh()->getVertexArray();
		IndexBuffer* iBuffer = renderable->getMesh()->getIndexBuffer();

		if (texture->hasTransparency())
		{
			MainRenderer::disable_culling();
		}

		shader->bind();
		texture->bind();
		vArray->bind();
		iBuffer->bind();

		// Create model matrix for model transformations
		glm::mat4 model(1.0);

		glm::mat4 jointTransforms[MAX_JOINTS];
		for (unsigned int i = 0; i < (jointVector.size() < MAX_JOINTS ? jointVector.size() : MAX_JOINTS); ++i)
		{
			jointTransforms[i] = jointVector[i];
		}

		//shader->setUniform4f("clipPlane", clipPlane);
		shader->setUniform1f("textureTiling", 1);
		shader->setUniformMatrix4fv("projection", camera->GetProjectionMatrix());
		shader->setUniformMatrix4fv("view", camera->GetViewMatrix());
		shader->setUniformMatrix4fv("model", model);
		shader->setUniformMatrix4fv("jointTransforms", jointTransforms[0]);

		glDrawElements(GL_TRIANGLES, iBuffer->getCount(), GL_UNSIGNED_INT, 0);

		iBuffer->unbind();
		vArray->unbind();
		texture->unbind();
		shader->unbind();
		MainRenderer::enable_culling();
	}
}

Shader* AnimationRenderer::getShader() {
	return shader;
}

void AnimationRenderer::setShader(Shader* shader) {
	this->shader = shader;
}