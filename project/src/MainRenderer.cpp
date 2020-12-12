#include "MainRenderer.h"
#include "Character.h"

Camera* MainRenderer::camera = NULL;
Character* MainRenderer::character = NULL;
std::set<Renderer*> MainRenderer::renderers;
std::set<GuiRenderer*> MainRenderer::guiRenderers;
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

void MainRenderer::load(GuiRenderer* renderer) {
	guiRenderers.insert(renderer);
}

void MainRenderer::unload(GuiRenderer* renderer) {
	guiRenderers.erase(renderer);
}

void MainRenderer::load(WaterRenderer* renderer) {
	waterRenderers.insert(renderer);
}

void MainRenderer::unload(WaterRenderer* renderer) {
	waterRenderers.erase(renderer);
}

Character* MainRenderer::getCharacter() {
	return character;
}
void MainRenderer::setCharacter(Character* _character) {
	character = _character;
}

void MainRenderer::render() {
	glm::vec3 cameraPosition = camera->GetPosition();
	float pitch = camera->GetPitch();

	// move camera under plane
	float distance = 2 * (cameraPosition.y - 4); //waterHeight
	cameraPosition.y -= distance;
	pitch *= -1;
	camera->SetPosition(cameraPosition);
	camera->setPitch(pitch);

	 //Render the scene in the reflection buffer
	waterFrameBuffer->bindReflectionBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	for (Renderer* renderer : renderers) {
		renderer->enableClipPlane(glm::vec4(0, 1, 0, -4)); //TODO change to water height if different than 0
		renderer->render();
		renderer->disableClipPlane();
	}
	waterFrameBuffer->unbindBuffer();

	// move camera back over plane
	cameraPosition.y += distance;
	pitch *= -1;
	camera->SetPosition(cameraPosition);
	camera->setPitch(pitch);

	waterFrameBuffer->bindRefractionBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Renderer* renderer : renderers) {
		renderer->enableClipPlane(glm::vec4(0, -1, 0, 4));
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

	for (GuiRenderer* renderer : guiRenderers) {
		renderer->render();
	}
}

void MainRenderer::enable_culling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MainRenderer::disable_culling() {
	glDisable(GL_CULL_FACE);
}