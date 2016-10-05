//
//  model.cpp
//  gol
//
//  Created by Joel Schmidt on 2/10/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#include <enginimus/model.hpp>
#include <enginimus/util.hpp>
#include <iostream>

using namespace std;

void Model::draw(Shader shader) {
    for(GLuint i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].draw(shader);
    }
}

void Model::loadModel(string path) {
    // TODO process model to remove duplicate vertices
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));
    
    this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    // Process all the node's meshes (if any)
    for(GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(mesh, scene));
    }
    
    // Then do the same for each of its children
    for(GLuint i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    
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
    // Process indices
    for(GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    // Process material
    //if(mesh->mMaterialIndex >= 0) {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, TEXTURE_TYPE_DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, TEXTURE_TYPE_SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //}
    
    return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> materialTextures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        GLboolean textureLoaded = false;
        
        // see if we've already loaded this texture
        for(GLuint j = 0; j < allModelTextures.size(); j++) {
            if(allModelTextures[j].path == str) {
                materialTextures.push_back(allModelTextures[j]);
                textureLoaded = true;
                break;
            }
        }
        
        if(!textureLoaded) {
            // If texture hasn't been loaded already, load it
            Texture texture;
            texture.id = util::TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str;
            materialTextures.push_back(texture);
            this->allModelTextures.push_back(texture);  // Add to loaded textures
        }
    }
    return materialTextures;
}




