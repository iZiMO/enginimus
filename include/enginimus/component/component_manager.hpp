//
// Created by Joel Schmidt on 9/10/2016.
//

#ifndef ENGINIMUS_COMPONENT_MANAGER_HPP
#define ENGINIMUS_COMPONENT_MANAGER_HPP

#include <vector>
#include <assert.h>
#include <enginimus/enginimus.h>

template<typename ComponentType>
class ComponentTypeManager {
protected:
    ComponentTypeManager() : components(MAX_ENTITIES) {}

    ComponentType& getComponent(EntityId id) {
        return components[id];
    }

    void setComponent(EntityId id, ComponentType component) {
        assert(id < MAX_ENTITIES);

        components[id] = component;
    }

private:
    std::vector<ComponentType> components;
};

template<typename... ComponentTypes>
class ComponentManager : private ComponentTypeManager<ComponentTypes> ... {
public:

    template<typename ComponentType>
    ComponentType &get(EntityId id) {
        return ComponentTypeManager<ComponentType>::getComponent(id);
    }

    template<typename ComponentType>
    void set(EntityId id, ComponentType component) {
        ComponentTypeManager<ComponentType>::setComponent(id, component);
    }
};


#endif //ENGINIMUS_COMPONENT_MANAGER_HPP
