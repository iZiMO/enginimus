//
// Created by Joel Schmidt on 10/10/2016.
//

#ifndef ENGINIMUS_ENTITY_MANAGER_HPP
#define ENGINIMUS_ENTITY_MANAGER_HPP

#include <vector>
#include <iostream>
#include "entity.hpp"
#include <enginimus/component/base_component.hpp>

class EntityManager {
public:

    EntityManager() : entities(MAX_ENTITIES) {}

    template<typename... ComponentTypes>
    void processEntities() {

        std::bitset<BaseComponent::numComponentTypes()> systemSignature;

        addComponentToSignature<ComponentTypes...>(systemSignature);
        // todo only iterate up to numAliveEntities
        for (int i=0; i<entities.size(); ++i) {
            if (systemSignature == (entities[i].getSignature()&systemSignature)) {
                // apply systemFunction to entity's components
                std::cout << "matched entity " << i << std::endl;
            }
        }
    }

    template<typename ComponentType>
    void addComponentToSignature(std::bitset<BaseComponent::numComponentTypes()>& signature) {
        signature.set(ComponentType::getId(), true);
    }

    std::vector<Entity> entities;
};

#endif //ENGINIMUS_ENTITY_MANAGER_HPP
