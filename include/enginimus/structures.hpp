//
//  structures.hpp
//  gol
//
//  Created by Joel Schmidt on 2/10/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#ifndef structures_h
#define structures_h

#include <glm/glm.hpp>
#include <string>
#include <GL/glew.h>
#include <assimp/scene.h>

using namespace std;

static const char* TEXTURE_TYPE_DIFFUSE = "textureDiffuse";
static const char* TEXTURE_TYPE_SPECULAR = "textureSpecular";

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    GLint id;
    string type; // diffuse / specular?
    aiString path;
};

#endif /* structures_h */
