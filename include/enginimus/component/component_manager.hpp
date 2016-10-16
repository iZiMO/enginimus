//
// Created by Joel Schmidt on 9/10/2016.
//

#ifndef ENGINIMUS_COMPONENT_MANAGER_HPP
#define ENGINIMUS_COMPONENT_MANAGER_HPP

#include <iostream>
#include <vector>
#include <assert.h>
#include <enginimus/enginimus.h>
#include "transform_component.hpp"
#include "render_component.hpp"

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
class ComponentManagerTemplate : private ComponentTypeManager<ComponentTypes> ... {
public:

    ComponentManagerTemplate() {
        std::cout << "Initialising component manager" << std::endl;
    }

    template<typename ComponentType>
    ComponentType &get(EntityId id) {
        return ComponentTypeManager<ComponentType>::getComponent(id);
    }

    template<typename ComponentType>
    void set(EntityId id, ComponentType component) {
        ComponentTypeManager<ComponentType>::setComponent(id, component);
    }
};


using ComponentManager = ComponentManagerTemplate<TransformComponent, RenderComponent>;

#endif //ENGINIMUS_COMPONENT_MANAGER_HPP
