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

#include <enginimus/render/free_look_camera.hpp>
#include <enginimus/render/render_component.hpp>
#include <enginimus/render/render_system.h>
#include <enginimus/input_system.hpp>

#include <enginimus/component/component_manager.hpp>


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

struct PositionComponent {
    std::string val;
};

struct BehaviourComponent {
};

using Manager = ComponentManager
        <
        PositionComponent,
        BehaviourComponent
        >;


int main() {

    Manager manager;

    PositionComponent pos;
    pos.val = "hello";
    manager.set(0, pos);
    cout << manager.get<PositionComponent>(0).val << endl;

//    RenderSystem renderSystem;
//    renderSystem.init(800, 600, "test");
//    renderSystem.setCamera(std::unique_ptr<Camera>(new FreeLookCamera()));
//
//    InputSystem inputSystem(renderSystem.getWindow());
//
//    // TODO move to either render system or "component manager"
//    RenderComponent box ("assets/Crate/Crate1.obj");
//    box.setModelMatrix(glm::translate(box.getModelMatrix(), glm::vec3(-5.0f, 0.0f, 0.0f)));
//    RenderComponent dude ("assets/nanosuit.obj");
//
//    renderSystem.registerComponent(box);
//    renderSystem.registerComponent(dude);
//
//    // Game loop
//    while(!glfwWindowShouldClose(renderSystem.getWindow()))
//    {
////        GLfloat currentFrame = (GLfloat)glfwGetTime();
////        deltaTime = currentFrame - lastFrame;
////        lastFrame = currentFrame;
//
//        inputSystem.processInput();
//        renderSystem.render();
//    }
//
//    glfwTerminate();
//    return 0;
}
