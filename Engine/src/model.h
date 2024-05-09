#pragma once

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"
#include "gameObject.h"

class Model : public GameObject {
public:
    Model(std::string path) {
        loadModel(path);
    }
    ~Model() {}

    glm::vec3 color;

    void draw(Shader& shader);

    // model data
    vector<Mesh> meshes;
    string directory;

private:
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};