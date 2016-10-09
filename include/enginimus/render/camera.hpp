//
// Created by Joel Schmidt on 6/10/2016.
//

#ifndef ENGINIMUS_CAMERA_HPP
#define ENGINIMUS_CAMERA_HPP

#include <glm/detail/type_mat.hpp>

class Camera {
public:
    virtual glm::mat4 getProjection(float windowWidth, float windowHeight) const = 0;
    virtual glm::mat4 getView() const = 0;
};

#endif //ENGINIMUS_CAMERA_HPP
