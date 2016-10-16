//
// Created by Joel Schmidt on 15/10/2016.
//

#ifndef ENGINIMUS_TRANSFORM_COMPONENT_HPP
#define ENGINIMUS_TRANSFORM_COMPONENT_HPP

#include <glm/matrix.hpp>
#include "component_types.hpp"

struct TransformComponent {
    static ComponentType getType();

    glm::mat4 transform;
};

#endif //ENGINIMUS_TRANSFORM_COMPONENT_HPP
