//
// Created by Joel Schmidt on 9/10/2016.
//

#ifndef ENGINIMUS_ENTITY_HPP
#define ENGINIMUS_ENTITY_HPP

#include <enginimus/enginimus.h>
#include <bitset>
#include <type_traits>
#include <enginimus/component/component_types.hpp>

using EntitySignature = std::bitset<ComponentType::NUM_COMPONENTS>;

class Entity {
public:
    // todo think of better way to auto-assign id
    Entity() { id = nextId++; }
    //Entity(EntityId entityId, std::string entityName) : id(entityId), name(entityName) {}
    void enableComponent(ComponentType componentType) { signature.set(componentType, true); }
    void disableComponent(ComponentType componentType) { signature.set(componentType, false); }
    bool hasComponent(ComponentType componentType) { return signature[componentType]; }

    const EntitySignature& getSignature() const { return signature; }
    const EntityId& getId() const { return id; }
private:
    // index into component vectors
    EntityId id;
    std::string name;

    /// Each bit represents a component type. @sa Component#getId()
    /// Each set bit indicates that this entity has that component type.
    EntitySignature signature;

    static EntityId nextId;
};

#endif //ENGINIMUS_ENTITY_HPP
