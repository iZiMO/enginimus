//
// Created by Joel Schmidt on 9/10/2016.
//

#ifndef ENGINIMUS_ENTITY_HPP
#define ENGINIMUS_ENTITY_HPP

#include <enginimus/enginimus.h>
#include <bitset>
#include <type_traits>
#include <enginimus/component/component.hpp>

class Entity {
public:
    Entity(std::string entityName) : name(entityName) {}
    void enableComponent(ComponentId componentId) { signature.set(componentId, true); }
    void disableComponent(ComponentId componentId) { signature.set(componentId, false); }
    bool hasComponent(ComponentId componentId) { return signature[componentId]; }
private:
    // index into component vectors
    EntityId id;
    std::string name;
    std::bitset<Component::numComponents()> signature; // each set bit indicates that this entity has that component type
};

#endif //ENGINIMUS_ENTITY_HPP
