//
// Created by Joel Schmidt on 23/10/2016.
//

#ifndef ENGINIMUS_INPUT_CONTEXT_HPP
#define ENGINIMUS_INPUT_CONTEXT_HPP

#include <enginimus/input/input.hpp>
#include <map>

using namespace std;

class InputContext {
    map<int, Action> actionMap;
    map<int, State> stateMap;
public:
    InputContext();
    void processKey(int key, int action, int mods, FrameInput& frameInput);
};

#endif //ENGINIMUS_INPUT_CONTEXT_HPP
