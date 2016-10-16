//
//  model.hpp
//
//  Created by Joel Schmidt on 2/10/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#ifndef ENGINIMUS_RENDER_COMPONENT_HPP
#define ENGINIMUS_RENDER_COMPONENT_HPP

#include <stdio.h>
#include <vector>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <enginimus/render/mesh.hpp>
#include <enginimus/component/component_types.hpp>

using namespace std;

struct RenderComponent {
    static ComponentType getType();

    /*  RenderComponent Data  */
    vector<Mesh> meshes;
    //Shader shader; // TODO embed shader here
    //vector<Texture> allModelTextures;
    string directory;
};

#endif /* ENGINIMUS_RENDER_COMPONENT_HPP */
