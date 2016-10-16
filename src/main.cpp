//
//  main.cpp
//  gol
//
//  Created by Joel Schmidt on 30/08/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

// GLEW
#define GLEW_STATIC

#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

// Matrix / vector maths library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <enginimus/component/component_manager.hpp>
#include <enginimus/component/render_component.hpp>

#include <enginimus/render/render_system.h>
#include <enginimus/render/free_look_camera.hpp>

#include <enginimus/input_system.hpp>
#include <enginimus/entity/entity_manager.hpp>
#include <enginimus/render/model_loader.hpp>

using namespace std;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

EntityId numEntities = 0;

EntityId createEntity(EntityManager& entityManager, shared_ptr<ComponentManager> componentManager,
                  ModelLoader& modelLoader, string modelPath) {

    RenderComponent render;
    modelLoader.loadModel(modelPath, render);
    componentManager->set(numEntities, render);
    entityManager.entities[numEntities].enableComponent(RenderComponent::getType());

    TransformComponent transform;
    componentManager->set(numEntities, transform);
    entityManager.entities[numEntities].enableComponent(TransformComponent::getType());

    return ++numEntities;
}

int main() {
    shared_ptr<ComponentManager> componentManager = make_shared<ComponentManager>();
    EntityManager entityManager (componentManager);

    RenderSystem renderSystem;
    renderSystem.init(800, 600, "test");
    renderSystem.setCamera(unique_ptr<Camera>(new FreeLookCamera()));

    InputSystem inputSystem(renderSystem.getWindow());


    ModelLoader modelLoader;

    EntityId box = createEntity(entityManager, componentManager, modelLoader, "assets/Crate/Crate1.obj");
    TransformComponent transform = componentManager->get<TransformComponent>(box);
    transform.transform = glm::translate(transform.transform, glm::vec3(0, 0, -5));

    EntityId dude = createEntity(entityManager, componentManager, modelLoader, "assets/nanosuit.obj");

    // Game loop
    while(!glfwWindowShouldClose(renderSystem.getWindow()))
    {
//        GLfloat currentFrame = (GLfloat)glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;

        inputSystem.processInput();
        renderSystem.render(entityManager);
    }

    glfwTerminate();
    return 0;
}
