//
// Created by Joel Schmidt on 10/10/2016.
//

#ifndef ENGINIMUS_ENTITY_MANAGER_HPP
#define ENGINIMUS_ENTITY_MANAGER_HPP

#include <vector>
#include <iostream>
#include <functional>
#include <enginimus/entity/entity.hpp>
#include <enginimus/component/component_manager.hpp>

class EntityManager {
public:

    EntityManager(std::shared_ptr<ComponentManager> componentManager)
            : entities(MAX_ENTITIES),
                componentManager(componentManager) {}

    template<typename ...ComponentT>
    void processEntities(std::function<void (ComponentT&...)> systemLogic) {

        EntitySignature systemSignature;

        addComponentsToSignature<ComponentT...>(systemSignature);
        // todo only iterate up to numAliveEntities
        for (int i=0; i<entities.size(); ++i) {
            if (systemSignature == (entities[i].getSignature() & systemSignature)) {
                //std::cout << "matched entity " << i << std::endl;
                systemLogic(componentManager->get<ComponentT>(entities[i].getId())...);
            }
        }
    }

    template<typename ...ComponentT>
    void addComponentsToSignature(EntitySignature& signature) {
        addComponentTypesToSignature(signature, ComponentT::getType()...);
    }

    template<typename ...Id>
    void addComponentTypesToSignature(EntitySignature& signature, Id... ids) {
        std::vector<ComponentType> idList = {ids...};
        for (int i=0; i<idList.size(); ++i) {
            signature.set(idList[i], true);
        }
    }

    std::vector<Entity> entities;
    std::shared_ptr<ComponentManager> componentManager;
};

#endif //ENGINIMUS_ENTITY_MANAGER_HPP
