//#pragma once
//#include <set>
//#include <vector>
//#include <string>
//#include <iostream>
//#include <glad/glad.h>
//#include <glm/glm.hpp>
//
//#include "SDL_opengl.h"
//#include "FreeImage.h"
//#include "Mesh.h"
//
//struct TriangleMesh {
//    std::vector<glm::vec4> vertices;
//    std::vector<glm::vec3> normals;
//    std::vector<glm::vec2> texcoords;
//    std::vector<unsigned int> indices;
//
//    GLuint vbo[4];
//
//    // material data:
//    glm::vec3 diffuse;          // diffuse coefficient
//    glm::vec3 specular;         // specular coefficient
//    glm::vec3 transmission;     // transmission coefficient
//    float ior;              // index of refraction
//    float phong;            // phong exponent
//    int   diffuseTextureID{ -1 };
//};
//
////struct Texture {
////    int id;
////};
//
////struct Model {
////    ~Model()
////    {
////        for (auto mesh : meshes) delete mesh;
////        //for (auto texture : textures) delete texture;
////    }
////
////    std::vector<TriangleMesh*> meshes;
////    std::vector<int>      textures;
////    //! bounding box of all vertices in the model
////    //glm::box3 bounds;
////};
////
////Model* loadOBJ(const std::string& objFile);
////void draw()
//
//class Model
//{
//    std::vector<int> textures;
//    //std::vector<TriangleMesh*> meshes;
//    void loadObj(const std::string& objFile);
//public:
//    std::vector<Mesh*> meshes;
//    Model(const std::string& objFile);
//    void draw();
//};