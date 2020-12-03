//#include "Model.h"
//#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"
//
//namespace std {
//    inline bool operator<(const tinyobj::index_t& a, const tinyobj::index_t& b)
//    {
//        if (a.vertex_index < b.vertex_index) return true;
//        if (a.vertex_index > b.vertex_index) return false;
//
//        if (a.normal_index < b.normal_index) return true;
//        if (a.normal_index > b.normal_index) return false;
//
//        if (a.texcoord_index < b.texcoord_index) return true;
//        if (a.texcoord_index > b.texcoord_index) return false;
//
//        return false;
//    }
//}
//
//unsigned int TextureFromFile(
//    std::map<std::string, int>& knownTextures, 
//    std::string name, 
//    const std::string& directory)
//{
//    if (name == "")
//        return -1;
//
//    if (knownTextures.find(name) != knownTextures.end())
//        return knownTextures[name];
//    
//    std::string filename = directory + '/' + name;
//
//    GLuint textureID;
//    glGenTextures(1, &textureID);
//
//    //CARGAR IMAGEN
//    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename.c_str());
//    FIBITMAP* bitmap = FreeImage_Load(fif, filename.c_str());
//    bitmap = FreeImage_ConvertTo24Bits(bitmap);
//    int w = FreeImage_GetWidth(bitmap);
//    int h = FreeImage_GetHeight(bitmap);
//    void* data = FreeImage_GetBits(bitmap);
//    //FIN CARGAR IMAGEN
//
//    if (data)
//    {
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
//        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//        //FIN TEXTURAs
//        FreeImage_Unload(bitmap);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << name << std::endl;
//    }
//
//    knownTextures[name] = textureID;
//    return textureID;
//}
//
//int addVertex(
//    TriangleMesh* mesh, 
//    tinyobj::attrib_t& attributes,
//    const tinyobj::index_t& idx,
//    std::map<tinyobj::index_t, int>& knownVertices)
//{
//    if (knownVertices.find(idx) != knownVertices.end())
//        return knownVertices[idx];
//
//    const glm::vec3* vertex_array = (const glm::vec3*)attributes.vertices.data();
//    const glm::vec3* normal_array = (const glm::vec3*)attributes.normals.data();
//    const glm::vec2* texcoord_array = (const glm::vec2*)attributes.texcoords.data();
//
//    int newID = (int)mesh->vertices.size();
//    knownVertices[idx] = newID;
//
//    mesh->vertices.push_back(glm::vec4(vertex_array[idx.vertex_index],1));
//    if (idx.normal_index >= 0) {
//        while (mesh->normals.size() < mesh->vertices.size())
//            mesh->normals.push_back(normal_array[idx.normal_index]);
//    }
//    if (idx.texcoord_index >= 0) {
//        while (mesh->texcoords.size() < mesh->vertices.size())
//            mesh->texcoords.push_back(texcoord_array[idx.texcoord_index]);
//    }
//
//    // just for sanity's sake:
//    if (mesh->texcoords.size() > 0)
//        mesh->texcoords.resize(mesh->vertices.size());
//    // just for sanity's sake:
//    if (mesh->normals.size() > 0)
//        mesh->normals.resize(mesh->vertices.size());
//
//    return newID;
//}
//
//void Model::loadObj(const std::string& objFile)
//{
//    //Model* model = new Model;
//
//    const std::string modelDir = objFile.substr(0, objFile.rfind('/') + 1);
//
//    tinyobj::attrib_t attributes;
//    std::vector<tinyobj::shape_t> shapes;
//    std::vector<tinyobj::material_t> materials;
//
//    std::string warn;
//    std::string err;
//
//    bool readOK = tinyobj::LoadObj(&attributes, &shapes, &materials, &err, &err, objFile.c_str(), modelDir.c_str(), true);
//
//    if (!readOK) {
//        throw std::runtime_error("Could not read OBJ model from " + objFile + " : " + err);
//    }
//
//    if (materials.empty()) {
//        throw std::runtime_error("could not parse materials ...");
//    }
//
//    std::cout << "Done loading obj file - found " << shapes.size() << " shapes with " << materials.size() << " materials" << std::endl;
//
//    for (tinyobj::shape_t shape : shapes) {
//        std::cout << shape.name <<'a' << std::endl;
//        // obtain list of material ids without duplicates
//        std::set<int> materialIDs;
//        for (auto faceMatID : shape.mesh.material_ids) materialIDs.insert(faceMatID);
//
//        std::map<tinyobj::index_t, int> knownVertices;
//        std::map<std::string, int>      knownTextures;
//
//        for (int materialID : materialIDs) {
//            TriangleMesh* mesh = new TriangleMesh;
//
//            for (int faceID = 0; faceID < shape.mesh.material_ids.size(); faceID++) {
//                if (shape.mesh.material_ids[faceID] != materialID) continue;
//                tinyobj::index_t idx0 = shape.mesh.indices[3 * faceID + 0];
//                tinyobj::index_t idx1 = shape.mesh.indices[3 * faceID + 1];
//                tinyobj::index_t idx2 = shape.mesh.indices[3 * faceID + 2];
//
//                mesh->indices.push_back(addVertex(mesh, attributes, idx0, knownVertices));
//                mesh->indices.push_back(addVertex(mesh, attributes, idx1, knownVertices));
//                mesh->indices.push_back(addVertex(mesh, attributes, idx2, knownVertices));
//                mesh->diffuse = (const glm::vec3&)materials[materialID].diffuse;
//            }
//
//        //    //mesh->diffuseTextureID = loadTexture(model,
//        //    //    knownTextures,
//        //    //    materials[materialID].diffuse_texname,
//        //    //    modelDir);
//            std::cout << materials[materialID].diffuse_texname << " " << modelDir << std::endl;
//            int textureId = TextureFromFile(knownTextures, materials[materialID].diffuse_texname, modelDir);
//            mesh->diffuseTextureID = textureId;
//            textures.push_back(textureId);
//
//            std::string filename = modelDir + '/' + materials[materialID].diffuse_texname;
//            Texture* tex = new Texture(filename);
//
//            if (mesh->vertices.empty())
//                delete mesh;
//            else {
//                //Mesh* nueva = new Mesh(mesh->vertices, mesh->texcoords, mesh->normals, mesh->indices, tex);
//                //meshes.push_back(nueva);
//            }
//        }
//    }
//}
//
//Model::Model(const std::string& objFile) {
//    loadObj(objFile);
//
//    //std::vector<glm::vec4> vert = {
//    //	glm::vec4(-0.5, 0.0, 0.0, 1.0),
//    //	glm::vec4(0.5, 0.0, 0.0, 1.0),
//    //	glm::vec4(0.0, 0.5, 0.0, 1.0),
//    //};
//
//    //std::vector<glm::vec2> uvs = {
//    //	glm::vec2(0.0, 0.0),
//    //	glm::vec2(1.0, 0.0),
//    //	glm::vec2(1.0, 1.0)
//    //};
//
//    //std::vector<glm::vec3> norms = {
//    //	glm::vec3(0.0, 0.0, 1.0),
//    //	glm::vec3(0.0, 0.0, 1.0),
//    //	glm::vec3(0.0, 0.0, 1.0),
//    //};
//
//    //std::vector<unsigned int> ind = { 0,1,2 };
//
//    //Texture* tex = new Texture("../kakashi.PNG");
//    //Mesh* nueva = new Mesh(vert, uvs, norms, ind, tex);
//    //this->meshes.push_back(nueva);
//
//    //Mesh* nu = new Mesh(vert, uvs, norms, ind, a.meshes[0]->getTexture());
//    //a.meshes.push_back(nu);
//
//    //for (TriangleMesh* mesh : meshes) {
//    //    //std::vector<float> reduced;
//    //    //for (int i = 0; i < mesh->vertices.size(); i++) {
//    //    //    reduced.push_back(mesh->vertex[i].x);
//    //    //    reduced.push_back(mesh->vertex[i].y);
//    //    //    reduced.push_back(mesh->vertex[i].z);
//    //    //}
//    //    //GLuint vao;
//    //    //glGenVertexArrays(1, &vao); // allocate & assign a Vertex Array Object (VAO)
//    //    //glBindVertexArray(vao); // bind VAO as current object
//    //    glGenBuffers(4, mesh->vbo); // allocate two Vertex Buffer Objects (VBO)
//
//    //    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[0]); // bind first VBO as active buffer object
//    //    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(GLfloat), mesh->vertices.data(), GL_STATIC_DRAW);
//
//    //    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[1]); // bind first VBO as active buffer object
//    //    glBufferData(GL_ARRAY_BUFFER, mesh->normals.size() * sizeof(GLfloat), mesh->normals.data(), GL_STATIC_DRAW);
//
//    //    //glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[2]); // bind first VBO as active buffer object
//    //    //glBufferData(GL_ARRAY_BUFFER, mesh->texcoord.size() * sizeof(GLfloat), mesh->texcoord.data(), GL_STATIC_DRAW);
//
//    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbo[3]); // bind first VBO as active buffer object
//    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * 3 * sizeof(GLfloat), mesh->indices.data(), GL_STATIC_DRAW);
//    //}
//}
//
//float ra = 0;
//
//void Model::draw() {
//    for (Mesh* mesh : meshes) {
//        Shader* shader = mesh->getShader();
//        Texture* texture = mesh->getTexture();
//        VertexArray* vArray = mesh->getVertexArray();
//        IndexBuffer* iBuffer = mesh->getIndexBuffer();
//
//        shader->bind();
//        texture->bind();
//        vArray->bind();
//        iBuffer->bind();
//
//        // Create perspective projection matrix
//        glm::mat4 projection = glm::perspective(45.0f, 1.f, 0.1f, 2000.f);
//
//        // Create view matrix for the camera
//        glm::mat4 view = glm::lookAt(glm::vec3(-1500,100,0), glm::vec3(0,0,0),glm::vec3(0,1,0));
//        ra += 0.00001; //for camera rotation
//        view = glm::rotate(view, ra, glm::vec3(0.0f, 1.0f, 0.0f));
//
//        // Create model matrix for model transformations
//        glm::mat4 model(1.0);
//
//        shader->setUniform1f("textureTiling", 1);
//        shader->setUniformMatrix4fv("projection", projection);
//        shader->setUniformMatrix4fv("view", view);
//        shader->setUniformMatrix4fv("model", model);
//
//        glDrawElements(GL_TRIANGLES, iBuffer->getCount(), GL_UNSIGNED_INT, 0);
//
//        iBuffer->unbind();
//        vArray->unbind();
//        texture->unbind();
//        shader->unbind();
//    }
//}