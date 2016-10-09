//
// Created by Joel Schmidt on 9/10/2016.
//

#ifndef ENGINIMUS_COMPONENT_HPP
#define ENGINIMUS_COMPONENT_HPP


#include <cstddef>
#include "base_component.hpp"

template<typename T>
class Component : BaseComponent {
public:
    size_t getId() { return id; }
    static size_t numComponentTypes();
private:
    static size_t id;
};
template<typename T>
size_t Component<T>::id = BaseComponent::nextId++;
template<typename T>
size_t Component<T>::numComponentTypes() { return BaseComponent::nextId; }


#endif //ENGINIMUS_COMPONENT_HPP
