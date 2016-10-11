//
// Created by Joel Schmidt on 9/10/2016.
//

#ifndef ENGINIMUS_BASE_COMPONENT_HPP
#define ENGINIMUS_BASE_COMPONENT_HPP

#include <cstddef>

class BaseComponent {
public:
    static constexpr size_t numComponentTypes();
protected:
    static size_t nextId;
};

#endif //ENGINIMUS_BASE_COMPONENT_HPP
