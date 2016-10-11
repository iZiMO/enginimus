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
    // todo think of better way to auto-assign id
    Entity() { id = nextId++; }
    //Entity(EntityId entityId, std::string entityName) : id(entityId), name(entityName) {}
    void enableComponent(ComponentId componentId) { signature.set(componentId, true); }
    void disableComponent(ComponentId componentId) { signature.set(componentId, false); }
    bool hasComponent(ComponentId componentId) { return signature[componentId]; }

    const std::bitset<BaseComponent::numComponentTypes()>& getSignature() const { return signature; }
private:
    // index into component vectors
    EntityId id;
    std::string name;

    /// Each bit represents a component type. @sa Component#getId()
    /// Each set bit indicates that this entity has that component type.
    std::bitset<BaseComponent::numComponentTypes()> signature;

    static EntityId nextId;
};

EntityId Entity::nextId = 0;

#endif //ENGINIMUS_ENTITY_HPP
