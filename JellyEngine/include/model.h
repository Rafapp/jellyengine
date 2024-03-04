#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "gameObject.h"

using namespace std;

class PhysicsObject; // forward declaration

class Model : public GameObject{
public:
	Model(char* path);
    ~Model() {}

    glm::vec3 color;

    PhysicsObject* physicsObject; // Use a pointer to avoid circular dependencies


    void update(float deltaTime);
	void draw(Shader& shader);

private:
    // model data
    vector<Mesh> meshes; 
    string directory;

    void loadModel(string path); // load the model from a file
    void processNode(aiNode* node, const aiScene* scene); // process each node in the model
    Mesh processMesh(aiMesh* mesh, const aiScene* scene); // process each mesh in the model
};