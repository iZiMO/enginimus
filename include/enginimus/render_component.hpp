//
//  model.hpp
//
//  Created by Joel Schmidt on 2/10/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#ifndef ENGINIMUS_RENDER_COMPONENT_HPP
#define ENGINIMUS_RENDER_COMPONENT_HPP

#include "mesh.hpp"

#include <stdio.h>
#include <vector>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class RenderComponent {
public:
    /*  Functions   */
    RenderComponent(const GLchar* path) {
        this->loadModel(path);
        this->model = glm::mat4();
    }

    void setModelMatrix(const glm::mat4 model) { this->model = model; }
    inline const glm::mat4& getModelMatrix() const { return model; }
    inline const vector<Mesh>& getMeshes() const { return meshes; }
private:
    /*  RenderComponent Data  */
    glm::mat4 model;
    vector<Mesh> meshes;
    vector<Texture> allModelTextures;
    string directory;

    /*  Functions   */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

#endif /* ENGINIMUS_RENDER_COMPONENT_HPP */
