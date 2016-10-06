//
// Created by Joel Schmidt on 6/10/2016.
//

#include <enginimus/input_system.hpp>

InputSystem* InputSystem::instance;

// Is called whenever a key is pressed/released via GLFW
void InputSystem::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS) {
        keys[key] = true;
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

//    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
//        toggle = !toggle;
//    }

}


void InputSystem::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    // dispatch to camera, etc.
    //camera.onMouseMoved(xpos, ypos);
}

void InputSystem::processInput() {
    glfwPollEvents();
}
