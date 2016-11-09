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

#include <enginimus/input/input_system.hpp>
#include <enginimus/entity/entity_manager.hpp>
#include <enginimus/render/model_loader.hpp>

using namespace std;

EntityId numEntities = 0;

EntityId createEntity(EntityManager& entityManager, ModelLoader& modelLoader, string modelPath) {

    RenderComponent render;
    modelLoader.loadModel(modelPath, render);
    TransformComponent transform;
    entityManager.setComponent(numEntities, render);
    entityManager.setComponent(numEntities, transform);

    return numEntities++;
}

void update() {
    // update simulation
}

int main() {
    shared_ptr<ComponentManager> componentManager = make_shared<ComponentManager>();
    EntityManager entityManager (componentManager);

    RenderSystem renderSystem;
    renderSystem.init(800, 600, "test");
    renderSystem.setCamera(unique_ptr<Camera>(new FreeLookCamera(componentManager)));

    InputSystem inputSystem(renderSystem.getWindow());
    shared_ptr<InputContext> inputContext = make_shared<InputContext>();
    inputSystem.setContext(inputContext);

    ModelLoader modelLoader;

    EntityId box = createEntity(entityManager, modelLoader, "assets/Crate/Crate1.obj");
    EntityId dude = createEntity(entityManager, modelLoader, "assets/nanosuit.obj");

    TransformComponent transform = componentManager->get<TransformComponent>(box);
    transform.transform = glm::translate(transform.transform, glm::vec3(0, 0, -5));



    const double MS_PER_UPDATE = 1000 / 60;

    // Game loop base off http://gameprogrammingpatterns.com/game-loop.html
    double previous = glfwGetTime();
    double lag = 0.0;
    while (!glfwWindowShouldClose(renderSystem.getWindow()))
    {
        double current = glfwGetTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        inputSystem.processInput();

        while (lag >= MS_PER_UPDATE)
        {
            update();
            lag -= MS_PER_UPDATE;
        }

        renderSystem.render(entityManager);
    }

    glfwTerminate();
    return 0;
}
