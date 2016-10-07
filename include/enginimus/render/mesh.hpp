//
//  mesh.hpp
//  gol
//
//  Created by Joel Schmidt on 2/10/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#ifndef ENGINIMUS_MESH_HPP
#define ENGINIMUS_MESH_HPP

#include <stdio.h>
#include <vector>
#include "structures.hpp"
#include "shader.h"

using namespace std;

class Mesh {
public:
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

    inline GLuint getVAO() const { return VAO; }
    inline const vector<Texture>& getTextures() const { return textures; }
    inline const int getNumIndices() const { return (int)indices.size(); }
private:
    /*  Render data  */
    GLuint VAO, VBO, EBO;
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    void setupMesh();
};

#endif /* ENGINIMUS_MESH_HPP */
