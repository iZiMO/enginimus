//
// Created by Joel Schmidt on 6/10/2016.
//

#ifndef ENGINIMUS_INPUT_SYSTEM_HPP
#define ENGINIMUS_INPUT_SYSTEM_HPP


#include <GLFW/glfw3.h>
#include <memory>
#include <enginimus/input/input.hpp>
#include <enginimus/input/input_context.hpp>

class InputSystem {
public:
    InputSystem(GLFWwindow *window) {
        instance = this;
        // Set the required callback functions
        glfwSetKeyCallback(window, InputSystem::keyCallbackDispatch);
        // Capture mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, InputSystem::mouseCallbackDispatch);
    }

    void setContext(std::shared_ptr<InputContext> inputContext);

    // GLFW callbacks
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);

    // process and dispatch
    void processInput();
private:
    FrameInput frameInput;
    std::shared_ptr<InputContext> inputContext;


    // TODO separate GLFW input from input system
    static InputSystem *instance;
    static void keyCallbackDispatch(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if(instance) {
            instance->keyCallback(window, key, scancode, action, mods);
        }
    }
    static void mouseCallbackDispatch(GLFWwindow* window, double xpos, double ypos)
    {
        if(instance) {
            instance->mouseCallback(window, xpos, ypos);
        }
    }
};


#endif //ENGINIMUS_INPUT_SYSTEM_HPP
