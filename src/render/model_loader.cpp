//
// Created by Joel Schmidt on 16/10/2016.
//

#include <enginimus/render/model_loader.hpp>
#include <enginimus/util.hpp>

#include <iostream>

using namespace std;

void ModelLoader::loadModel(const string path, RenderComponent& renderComponent) {
    // TODO process model to remove duplicate vertices
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }

    renderComponent.directory = path.substr(0, path.find_last_of('/'));

    vector<Texture> textureCache;
    processNode(scene->mRootNode, scene, textureCache, renderComponent);
}

void ModelLoader::processNode(aiNode* node, const aiScene* scene, vector<Texture> &textureCache, RenderComponent& renderComponent) {
    // Process all the node's meshes (if any)
    for(GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        renderComponent.meshes.push_back(this->processMesh(mesh, scene, renderComponent.directory, textureCache));
    }

    // Then do the same for each of its children
    for(GLuint i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene, textureCache, renderComponent);
    }
}

Mesh ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene, const string directory, vector<Texture> &textureCache) {
    cout << "Processing mesh " << mesh->mName.C_Str() << endl;
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    cout << "  vertices: " << mesh->mNumVertices << endl;
    for(GLuint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        // Process vertex positions, normals and texture coordinates
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

        vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        glm::vec2 vec;
        if(mesh->mTextureCoords[0]) {
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
        } else {
            vec.x = 0.f;
            vec.y = 0.f;
        }
        vertex.texCoords = vec;

        vertices.push_back(vertex);
    }

    cout << "  faces: " << mesh->mNumFaces << endl;
    // Process indices
    for(GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process material
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    cout << "  loading material " << mesh->mMaterialIndex << endl;
    vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, TEXTURE_TYPE_DIFFUSE, directory, textureCache);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, TEXTURE_TYPE_SPECULAR, directory, textureCache);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    return Mesh(vertices, indices, textures);
}

vector<Texture> ModelLoader::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string typeName, const string directory, vector<Texture> &textureCache) {
    vector<Texture> materialTextures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        cout << "    " << typeName << " - " << str.C_Str() << endl;
        bool textureLoaded = false;

        // see if we've already loaded this texture
        for(GLuint j = 0; j < textureCache.size(); j++) {
            if(textureCache[j].path == str) {
                materialTextures.push_back(textureCache[j]);
                textureLoaded = true;
                break;
            }
        }

        if(!textureLoaded) {
            // If texture hasn't been loaded already, load it
            Texture texture;
            texture.id = util::TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str;
            materialTextures.push_back(texture);
            textureCache.push_back(texture);  // Add to cached textures
        }
    }
    return materialTextures;
}