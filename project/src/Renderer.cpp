#include "Renderer.h"
#include "MainRenderer.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

using namespace std;

glm::vec3 calculateAverage(std::set<Renderable*> renderables) {
    float total = 0.0f;
    glm::vec3 average(0);
    for(Renderable* rendereable : renderables) {
       std::vector<glm::vec4> vertices = rendereable->getMesh()->getVertices();
        for (glm::vec4& vertix : vertices) { 
            total++;
            average.x += vertix.x;
            average.y += vertix.y;
            average.z += vertix.z;
        }
    }
    if (total == 0) {
        return average;
    }
    return glm::vec3(average.x/total, average.y/total, average.z/total);
}

Renderer::Renderer(Camera* camera, bool isCharacter) {
    this->camera = camera;
    this->clipPlaneEnabled = false;
    this->clipPlane = glm::vec4(0, -1, 0, 100000);
    this->shader = NULL;
	MainRenderer::load(this);
    this->isCharacter = isCharacter;
};
Renderer::~Renderer() {
	renderables.clear();
	MainRenderer::unload(this);
};

void Renderer::load(Renderable* renderable) {
	renderables.insert(renderable);
    this->averageVertix = calculateAverage(renderables);
}
void Renderer::unload(Renderable* renderable) {
	renderables.erase(renderable);
    this->averageVertix = calculateAverage(renderables);
}

void Renderer::clearMesh() {
	renderables.clear();
}

void Renderer::enableClipPlane(glm::vec4 clipPlane) {
	this->clipPlane = clipPlane;
	this->clipPlaneEnabled = true;
}

void Renderer::disableClipPlane() {
	this->clipPlane = glm::vec4(0, -1, 0, 100000); 
	this->clipPlaneEnabled = false;
}

void Renderer::render(std::set<Light*> lights) {
    (clipPlaneEnabled) ? glEnable(GL_CLIP_DISTANCE0) : glDisable(GL_CLIP_DISTANCE0);
	for (Renderable* renderable : renderables) {
		Shader* shader = getShader();
		Texture* texture = renderable->getTexture();
		VertexArray* vArray = renderable->getMesh()->getVertexArray();
		IndexBuffer* iBuffer = renderable->getMesh()->getIndexBuffer();

        if (texture->hasTransparency()) MainRenderer::disable_culling();

		shader->bind();
		texture->bind();
		vArray->bind();
		iBuffer->bind();

        shader->setUniform3f("cameraPosition", camera->GetPosition());
		shader->setUniform4f("clipPlane", clipPlane);
		shader->setUniform1f("textureTiling", 1);
		shader->setUniformMatrix4fv("projection", camera->GetProjectionMatrix());
		shader->setUniformMatrix4fv("view", camera->GetViewMatrix());
		shader->setUniformMatrix4fv("model", camera->GetModelMatrix(isCharacter));

        Light* light = *lights.begin();

        shader->setUniform3f("lightPosition", light->getPosition());
        shader->setUniform3f("lightColor", light->getColor());

		//shader->setUniform1f("textureTiling", renderable->getTextureTiling());
		//shader->setUniform3f("directionalLight.color", Light::color);
		//shader->setUniform1f("directionalLight.intensity", Light::intensity);
		//shader->setUniform3f("directionalLight.direction", Light::direction);
		//shader->setUniformMatrix4fv("gWorld", renderable->getTransform()->GetMatrix());

		glDrawElements(GL_TRIANGLES, iBuffer->getCount(), GL_UNSIGNED_INT, 0);

		iBuffer->unbind();
		vArray->unbind();
		texture->unbind();
		shader->unbind();
        MainRenderer::enable_culling();
	}
}

namespace std {
    inline bool operator<(const tinyobj::index_t& a, const tinyobj::index_t& b)
    {
        if (a.vertex_index < b.vertex_index) return true;
        if (a.vertex_index > b.vertex_index) return false;

        if (a.normal_index < b.normal_index) return true;
        if (a.normal_index > b.normal_index) return false;

        if (a.texcoord_index < b.texcoord_index) return true;
        if (a.texcoord_index > b.texcoord_index) return false;

        return false;
    }
}

unsigned int TextureFromFile(
    std::map<std::string, int>& knownTextures, 
    std::string name, 
    const std::string& directory)
{
    if (name == "")
        return -1;

    if (knownTextures.find(name) != knownTextures.end())
        return knownTextures[name];
    
    std::string filename = directory + '/' + name;

    GLuint textureID;
    glGenTextures(1, &textureID);

    //CARGAR IMAGEN
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename.c_str());
    FIBITMAP* bitmap = FreeImage_Load(fif, filename.c_str());
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    int w = FreeImage_GetWidth(bitmap);
    int h = FreeImage_GetHeight(bitmap);
    void* data = FreeImage_GetBits(bitmap);
    //FIN CARGAR IMAGEN

    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        //FIN TEXTURAs
        FreeImage_Unload(bitmap);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << name << std::endl;
    }

    knownTextures[name] = textureID;
    return textureID;
}

int addVertex(
    TriangleMesh* mesh, 
    tinyobj::attrib_t& attributes,
    const tinyobj::index_t& idx,
    std::map<tinyobj::index_t, int>& knownVertices)
{
    if (knownVertices.find(idx) != knownVertices.end())
        return knownVertices[idx];

    const glm::vec3* vertex_array = (const glm::vec3*)attributes.vertices.data();
    const glm::vec3* normal_array = (const glm::vec3*)attributes.normals.data();
    const glm::vec2* texcoord_array = (const glm::vec2*)attributes.texcoords.data();

    int newID = (int)mesh->vertices.size();
    knownVertices[idx] = newID;

    mesh->vertices.push_back(glm::vec4(vertex_array[idx.vertex_index],1));
    if (idx.normal_index >= 0) {
        while (mesh->normals.size() < mesh->vertices.size())
            mesh->normals.push_back(normal_array[idx.normal_index]);
    }
    if (idx.texcoord_index >= 0) {
        while (mesh->texcoords.size() < mesh->vertices.size())
            mesh->texcoords.push_back(texcoord_array[idx.texcoord_index]);
    }

    // just for sanity's sake:
    if (mesh->texcoords.size() > 0)
        mesh->texcoords.resize(mesh->vertices.size());
    // just for sanity's sake:
    if (mesh->normals.size() > 0)
        mesh->normals.resize(mesh->vertices.size());

    return newID;
}

void Renderer::loadObj(const std::string& objFile) {
    const std::string modelDir = objFile.substr(0, objFile.rfind('/') + 1);

    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool readOK = tinyobj::LoadObj(&attributes, &shapes, &materials, &err, &err, objFile.c_str(), modelDir.c_str(), true);

    if (!readOK) {
        throw std::runtime_error("Could not read OBJ model from " + objFile + " : " + err);
    }

    if (materials.empty()) {
        throw std::runtime_error("could not parse materials ...");
    }

    std::cout << "Done loading obj file - found " << shapes.size() << " shapes with " << materials.size() << " materials" << std::endl;

    for (tinyobj::shape_t shape : shapes) {
        // obtain list of material ids without duplicates
        std::set<int> materialIDs;
        for (auto faceMatID : shape.mesh.material_ids) materialIDs.insert(faceMatID);

        std::map<tinyobj::index_t, int> knownVertices;
        std::map<std::string, int>      knownTextures;

        for (int materialID : materialIDs) {
            TriangleMesh* mesh = new TriangleMesh;

            for (int faceID = 0; faceID < shape.mesh.material_ids.size(); faceID++) {
                if (shape.mesh.material_ids[faceID] != materialID) continue;
                tinyobj::index_t idx0 = shape.mesh.indices[3 * faceID + 0];
                tinyobj::index_t idx1 = shape.mesh.indices[3 * faceID + 1];
                tinyobj::index_t idx2 = shape.mesh.indices[3 * faceID + 2];

                mesh->indices.push_back(addVertex(mesh, attributes, idx0, knownVertices));
                mesh->indices.push_back(addVertex(mesh, attributes, idx1, knownVertices));
                mesh->indices.push_back(addVertex(mesh, attributes, idx2, knownVertices));
                mesh->diffuse = (const glm::vec3&)materials[materialID].diffuse;
            }


            if (mesh->vertices.empty())
                delete mesh;
            else {
                Mesh* nueva = new Mesh(mesh->vertices, mesh->texcoords, mesh->normals, mesh->indices);
                
                std::string filename = modelDir + '/' + materials[materialID].diffuse_texname;
                Texture* tex = new Texture(filename);

                Renderable* renderable = new Renderable();
                renderable->setMesh(nueva);
                renderable->setTexture(tex, 1.f);
                renderables.insert(renderable);
            }
        }
    }
    this->averageVertix = calculateAverage(renderables);
}

Shader* Renderer::getShader() {
    return shader;
}

void Renderer::setShader(Shader* shader) {
    this->shader = shader;
}

glm::vec3 Renderer::getAverageVertix() {
    return averageVertix;
}