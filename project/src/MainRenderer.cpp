#include "MainRenderer.h"
#include "Character.h"

float MainRenderer::lodEnabled = 1.f;
Camera* MainRenderer::camera = NULL;
Character* MainRenderer::character = NULL;
std::set<Light*> MainRenderer::lights; 
std::set<Renderer*> MainRenderer::renderers;
std::set<GuiRenderer*> MainRenderer::guiRenderers;
std::set<WaterRenderer*> MainRenderer::waterRenderers;

SkyboxRenderer* MainRenderer::skybox = NULL;
WaterFrameBuffer* MainRenderer::waterFrameBuffer = NULL;

void MainRenderer::init(Camera* camera) {
	MainRenderer::camera = camera;
	waterFrameBuffer = new WaterFrameBuffer();
	skybox = new SkyboxRenderer(camera);
}

void MainRenderer::load(Light* light) {
	lights.insert(light);
}

void MainRenderer::unload(Light* light) {
	lights.erase(light);
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
	glClearColor(skybox->getSkyColor().x, skybox->getSkyColor().y, skybox->getSkyColor().z, 1.0);					// set background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	// move camera under plane
	camera->moveCameraDown();

	//Render the scene in the reflection buffer
	waterFrameBuffer->bindReflectionBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	for (Renderer* renderer : renderers) {
		renderer->enableClipPlane(glm::vec4(0, 1, 0, -4 + 2.f)); //TODO change to water height if different than 0
		renderer->render(lights, skybox->getSkyColor());
		renderer->disableClipPlane();
		skybox->enableClipPlane(glm::vec4(0, 1, 0, -4));
		skybox->render();
		skybox->disableClipPlane();
	}
	waterFrameBuffer->unbindBuffer();

	// move camera back over plane
	camera->moveCameraUp();

	waterFrameBuffer->bindRefractionBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Renderer* renderer : renderers) {
		renderer->enableClipPlane(glm::vec4(0, -1, 0, 4 + 1.f));
		renderer->render(lights, skybox->getSkyColor());
		renderer->disableClipPlane();
		skybox->enableClipPlane(glm::vec4(0, -1, 0, 4));
		skybox->render();
		skybox->disableClipPlane();
	}
	waterFrameBuffer->unbindBuffer();

	for (Renderer* renderer : renderers) {
		renderer->render(lights, skybox->getSkyColor());
	}

	skybox->render();

	for (WaterRenderer* renderer : waterRenderers) {
		renderer->render(lights, waterFrameBuffer);
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

void MainRenderer::toggleLod() {
	lodEnabled = (lodEnabled == 1.f) ? 0.f : 1.f;
}
