//
// Created by Joel Schmidt on 23/10/2016.
//

#include <enginimus/input/input_context.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

InputContext::InputContext() {
    stateMap[GLFW_KEY_UP] = MOVE_FORWARD;
    stateMap[GLFW_KEY_DOWN] = MOVE_BACKWARD;
    stateMap[GLFW_KEY_LEFT] = TURN_LEFT;
    stateMap[GLFW_KEY_RIGHT] = TURN_RIGHT;

    actionMap[GLFW_KEY_ENTER] = PRIMARY_ACTION;
    actionMap[GLFW_KEY_SPACE] = SECONDARY_ACTION;
    actionMap[GLFW_KEY_ESCAPE] = QUIT;
}

void InputContext::processKey(int key, int action, int mods, FrameInput& frameInput) {
    if (action == GLFW_PRESS) {
        auto mappedAction = actionMap.find(key);
        if (mappedAction != actionMap.end()) {
            frameInput.actions[mappedAction->second] = true;
        }
        auto mappedState = stateMap.find(key);
        if (mappedState != stateMap.end()) {
            frameInput.states[mappedState->second] = true;
        }
    } else if (action == GLFW_RELEASE) {
        auto mappedState = stateMap.find(key);
        if (mappedState != stateMap.end()) {
            frameInput.states[mappedState->second] = false;
        }
    }
}

