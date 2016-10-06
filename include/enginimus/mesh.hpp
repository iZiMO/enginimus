//
//  mesh.hpp
//  gol
//
//  Created by Joel Schmidt on 2/10/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <stdio.h>
#include <vector>
#include "structures.hpp"
#include "shader.h"

using namespace std;

class Mesh {
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    /*  Functions  */
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
    void render(Shader shader, glm::mat4 model) const;
private:
    /*  Render data  */
    GLuint VAO, VBO, EBO;
    /*  Functions    */
    void setupMesh();
};

#endif /* mesh_hpp */
