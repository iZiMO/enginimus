//
// Created by Joel Schmidt on 9/11/2016.
//

#include <gtest/gtest.h>
#include "enginimus/entity/entity_manager.hpp"

// A new one of these is created for each test
class EntityManagerTest : public testing::Test
{
public:
    shared_ptr<ComponentManager> componentManager = make_shared<ComponentManager>();
    EntityManager *entityManager = new EntityManager(componentManager);
    int numExecutes = 0;

    virtual void SetUp() {
        TransformComponent comp1;
        entityManager->setComponent(5, comp1);
    }

    virtual void TearDown() {
        delete entityManager;
    }

    template<typename ...T>
    void executeSystem(T&... componentTypes) {
        numExecutes++;
    }
};

TEST_F(EntityManagerTest, MatchingSystemExecutes) {
    function<void(TransformComponent&)> func = [this](TransformComponent& transform) {
        executeSystem(transform);
    };
    entityManager->processEntities<TransformComponent>(func);

    ASSERT_TRUE(numExecutes == 1);
}

TEST_F(EntityManagerTest, NonMatchingSystemDoesNotExecute) {
    function<void(TransformComponent&,RenderComponent&)> func = [this](TransformComponent& transform, RenderComponent& render) {
        executeSystem(transform, render);
    };
    entityManager->processEntities<TransformComponent,RenderComponent>(func);

    ASSERT_TRUE(numExecutes == 0);
}