#include "GuiRenderer.h"
#include "MainRenderer.h"

GuiRenderer::GuiRenderer(Shader* shader) {
	this->shader = shader;
	std::vector<glm::vec2> vertices = {
		glm::vec2(-1, 1),
		glm::vec2(-1, -1),
		glm::vec2(1, 1),
		glm::vec2(1, -1),
	};

	Buffer* vertexBuffer = new Buffer(vertices);
	vertexArray = new VertexArray();
	vertexArray->addBuffer(vertexBuffer, 0);
	MainRenderer::load(this);
}

GuiRenderer::~GuiRenderer() {
	delete vertexArray;
	guis.clear();
	MainRenderer::unload(this);
}

void GuiRenderer::load(GuiTexture* gui) {
	guis.insert(gui);
}

void GuiRenderer::unload(GuiTexture* gui) {
	guis.erase(gui);
}

void GuiRenderer::render() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	shader->bind();
	for (GuiTexture* gui : guis) {
		Texture* texture = gui->tex;
		
		texture->bind();
		vertexArray->bind();

		glm::mat4 model(1.0);
		model = glm::translate(model, glm::vec3(gui->position, 0));
		model = glm::scale(model, glm::vec3(gui->scale, 1));

		shader->setUniformMatrix4fv("transformationMatrix", model);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		vertexArray->unbind();
		texture->unbind();
	}
	shader->unbind();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}