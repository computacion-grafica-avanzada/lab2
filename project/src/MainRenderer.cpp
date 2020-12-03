#include "MainRenderer.h"

Camera* MainRenderer::camera = NULL;
std::set<Renderer*> MainRenderer::renderers;
std::set<WaterRenderer*> MainRenderer::waterRenderers;
WaterFrameBuffer* MainRenderer::waterFrameBuffer = NULL;

void MainRenderer::init(Camera* camera) {
	MainRenderer::camera = camera;
	waterFrameBuffer = new WaterFrameBuffer();
}

void MainRenderer::load(Renderer* renderer) {
	renderers.insert(renderer);
}

void MainRenderer::unload(Renderer* renderer) {
	renderers.erase(renderer);
}

void MainRenderer::load(WaterRenderer* renderer) {
	waterRenderers.insert(renderer);
}

void MainRenderer::unload(WaterRenderer* renderer) {
	waterRenderers.erase(renderer);
}

void MainRenderer::render() {
	glm::vec3 cameraPosition = camera->GetPosition();
	float pitch = camera->GetPitch();

	// move camera under plane
	float distance = 2 * (cameraPosition.y - 15); //waterHeight
	cameraPosition.y -= distance;
	//cameraPosition.y *= -1;
	////pitch *= -1;
	camera->SetPosition(cameraPosition);
	//camera->SetPitch(pitch);

	// Render the scene in the reflection buffer
	waterFrameBuffer->bindReflectionBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	for (Renderer* renderer : renderers) {
		renderer->enableClipPlane(glm::vec4(0, 1, 0, -15)); //TODO change to water height if different than 0
		renderer->render();
		renderer->disableClipPlane();
	}
	waterFrameBuffer->unbindBuffer();

	//// move camera back over plane
	cameraPosition.y += distance;
	////pitch *= -1;
	camera->SetPosition(cameraPosition);
	//camera->SetPitch(pitch);

	waterFrameBuffer->bindRefractionBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Renderer* renderer : renderers) {
		renderer->enableClipPlane(glm::vec4(0, -1, 0, 15));
		renderer->render();
		renderer->disableClipPlane();
	}
	waterFrameBuffer->unbindBuffer();

	for (Renderer* renderer : renderers) {
		renderer->render();
	}

	for (WaterRenderer* renderer : waterRenderers) {
		renderer->render(waterFrameBuffer);
	}
}
