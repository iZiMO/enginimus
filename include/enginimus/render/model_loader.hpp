//
// Created by Joel Schmidt on 16/10/2016.
//

#ifndef ENGINIMUS_MODEL_LOADER_HPP
#define ENGINIMUS_MODEL_LOADER_HPP

#include <stdio.h>
#include <vector>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <enginimus/component/component_types.hpp>

#include <enginimus/render/mesh.hpp>
#include <enginimus/component/render_component.hpp>

class ModelLoader {
public:
    void loadModel(const string path, RenderComponent& renderComponent);

private:
    void processNode(aiNode* node, const aiScene* scene, vector<Texture> &textures, RenderComponent& renderComponent);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene, const string directory, vector<Texture> &textureCache);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string typeName, const string directory, vector<Texture> &textureCache);
};

#endif //ENGINIMUS_MODEL_LOADER_HPP
