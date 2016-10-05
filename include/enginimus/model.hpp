//
//  model.hpp
//
//  Created by Joel Schmidt on 2/10/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include "mesh.hpp"

#include <stdio.h>
#include <vector>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class Model {
public:
    /*  Functions   */
    Model(const GLchar* path) {
        this->loadModel(path);
        this->model = glm::mat4();
    }
    void draw(Shader shader);

    glm::mat4 model;
private:
    /*  Model Data  */
    vector<Mesh> meshes;
    vector<Texture> allModelTextures;
    string directory;

    /*  Functions   */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

#endif /* model_hpp */
