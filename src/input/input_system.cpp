//
// Created by Joel Schmidt on 6/10/2016.
//

#include <enginimus/input/input_system.hpp>
#include <iostream>

using namespace std;

InputSystem* InputSystem::instance;

void InputSystem::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // reset actions
    for (int i=0; i<NUM_ACTIONS; ++i) {
        frameInput.actions[i] = false;
    }
    inputContext->processKey(key, action, mods, frameInput);

    if (frameInput.actions[QUIT]) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


void InputSystem::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    // dispatch to camera, etc.
    //camera.onMouseMoved(xpos, ypos);
}

void InputSystem::processInput() {
    glfwPollEvents();
}

void InputSystem::setContext(std::shared_ptr<InputContext> inputContext) {
    this->inputContext = inputContext;
}
